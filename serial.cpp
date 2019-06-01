#include "serial.h"
#include "mainwindow.h"

#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QMessageBox>

Serial::Serial(MainWindow *parent)
{
    m_parent = parent;
    inData->reserve(100); // Just in case, reserve a buffer

    breakTimer->setSingleShot(true);
    breakTimer->setInterval(1000);

    connect(this, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Serial::handleError);

    connect(this, &QSerialPort::readyRead, this, &Serial::readSerial);

    connect(this, &Serial::motorShut, parent, &MainWindow::motorShut);

    connect(breakTimer, &QTimer::timeout, this, &Serial::stopBreak);
}

bool Serial::openSerialPort()
{
#if RPI
    this->setPortName("ttyAMA0");
    this->setBaudRate(QSerialPort::Baud2400);
#else
    this->setPortName("COM11");
    this->setBaudRate(QSerialPort::Baud57600);
#endif

    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);
    if(this->open(QIODevice::ReadWrite)) // If opening is succesful
    {
        m_parent->entrySerialLog->addLine("Port set to read-write");
        m_parent->entrySerialLog->addLine("Pulling low ->");
        this->setBreakEnabled(true);
        // Line needs to be held low to Power module to start communicating
        breakTimer->start();
        return true;
    }
    else
    {
        m_parent->entrySerialLog->addLine("Serial port open error - "+this->errorString());
        EntryErrors::addLine("Serial port open error - "+this->errorString());
        return false;
    }
}

void Serial::closeSerialPort()
{
    if (this->isOpen())
        this->close();
    m_parent->entrySerialLog->addLine("Disconnected");
}

void Serial::readSerial()
{
    // Read data into a QBytearray
    const QByteArray data = this->readAll();

    // Copy data to a QString for easier handling
    inData->append(QString::fromUtf8(data));

    while(inData->contains('\n') )//|| inData->contains('\r'))
    {
        // Get the first line-ending character and its index
        int i;
        if(inData->contains('\r'))
        {
            inData->remove('\r');
            i = inData->indexOf('\n');
        }
        else
            i = inData->indexOf('\n');

        /* Depending of the first character, do accordingly
         * Syntax:
         * e = end of data (e~)
         * ? = host presence / continue operation query (?h)
         * ! = critical condition occurred (over[!C]urrent, over[!V]oltage, under[!v]oltage or high [!T]emperature)
         * u = power is on (up)
         * s = power is shut (sh)
         * : = data point (Battery [c]urrent, battery [v]voltage, # battery unit cell number and its temperature ie. :0-00.0)
         */

        if(inData->at(0) == '!') // Handle critical errors immidiately if occurred
        {
            emit motorShut(true);
            if(inData->at(1) == 'C' && !overC)
            {
                overC = true;
                Notice::showText("Overcurrent detected!");
                EntryErrors::addLine("Overcurrent detected!");
            }
            else if(inData->at(1) == 'V' && !overV)
            {
                overV = true;
                Notice::showText("Overvoltage detected!");
                EntryErrors::addLine("Overvoltage detected!");
            }
            else if(inData->at(1) == 'T')
            {
                overT = true;
                Notice::showText("Overtemperature detected!");
                EntryErrors::addLine("Overtemperature detected!");
            }
            else if(inData->at(1) == 'v' && !underV)
            {
                underV = true;
                Notice::showText("Low voltage detected!");
                EntryErrors::addLine("Low voltage detected!");
            }
        }
        else if(inData->at(0) == 'e' || inData->at(0) == '~')
        {
            // If end of data received, inform to be ready to receive another batch
            if(m_parent->entryMotor->powerWanted) // Only if we want power on;
            {
                writeSerial("ok\n");
            }
        }
        else if(inData->at(0) == '?' && inData->at(1) == 'h')
        {
            if(m_parent->entryMotor->powerWanted) // Only if we want power on;
            {
                writeSerial("ok\n");
            }
        }
        else if(inData->at(0) == 'u' && inData->at(1) == 'p')
        {
            emit motorShut(false);
            overT = false;
            overV = false;
            overC = false;
            underV = false;
        }
        else if(inData->at(0) == 's' && inData->at(1) == 'h')
        {
            emit motorShut(true);
        }
        else if(inData->at(0) == ':')
        {
            if(inData->at(1) == 'c')
            {
                dataEntry = -1;
                display(inData->mid(2,i-2));
            }
            else if(inData->at(1) == 'v')
            {
                dataEntry = -2;
                display(inData->mid(2,i-2));
            }
            else
            {
                QString entryNum = inData->mid(1,inData->indexOf('-')-1); // Get the 1 or 2 number index
                dataEntry = entryNum.toInt(); // Change it to integer
                QString dataValue = inData->mid(inData->indexOf('-')+1,i-inData->indexOf('-')-1); // Get the value
                if(dataValue != "257.0") // Check if it's valid
                    display(dataValue);
                else
                    display("CRC"); // Otherwise it's CRC error
            }
        }
        else
        {
            // If first character wasn't any of the above, it was corrupted message
            EntryErrors::addLine("Unknown serial data received: "+inData->left(i));
        }

        // Last, add the message to serial log and remove it from the QString variable
        m_parent->entrySerialLog->addLine(inData->left(i));
        *inData = inData->remove(0,i+1);
    }
}


void Serial::writeSerial(const QByteArray &outData)
{
    this->write(outData);
    QByteArray temp = outData;
    temp.chop(1); // Delete nl after sending it
    m_parent->entrySerialLog->addLine(temp + " ------->");
}

void Serial::display(const QString &displayData)
{
    QString data;
    data = displayData;

    switch(dataEntry)
    {
    case -1:
        m_parent->meter->setAmp(data);
        break;

    case -2:
        m_parent->meter->setVolt(data);
        break;

    default:
        data.append("'C");
        m_parent->entryTemp->setTemp(dataEntry, data);
        break;
    }
}


void Serial::stopBreak()
{
    this->setBreakEnabled(false);
}

void Serial::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        Notice::showText("Serial port error!");
        m_parent->entrySerialLog->addLine("Serial port error - "+this->errorString());
        closeSerialPort();
    }
}


