#include "serial.h"
#include "mainwindow.h"

#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

Serial::Serial(MainWindow *parent)
{
    m_parent = parent;
    inData->reserve(100);

    breakTimer->setSingleShot(true);
    breakTimer->setInterval(1000);

    connect(this, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Serial::handleError);

    connect(this, &QSerialPort::readyRead,
            this, &Serial::readSerial);

    connect(this, &Serial::motorIsShut,
            parent, &MainWindow::toggleMotorEntry);

    connect(breakTimer, &QTimer::timeout,
            this, &Serial::stopBreak);
}

bool Serial::openSerialPort()
{
#if RPI
    this->setPortName("ttyAMA0");
    this->setBaudRate(QSerialPort::Baud9600);
#else
    this->setPortName("COM11");
    this->setBaudRate(QSerialPort::Baud57600);
#endif

    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);
    if(this->open(QIODevice::ReadWrite))
    {
        //m_parent->serialLogEntry->addLine("Connected");
        this->setBreakEnabled(true);
        breakTimer->start();
        return true;
    }
    else
    {
        //m_parent->errorsEntry->addLine("Serial port open error - "+this->errorString());
        return false;
    }
}

void Serial::closeSerialPort()
{
    if (this->isOpen())
        this->close();
    //m_parent->serialLogEntry->addLine("Disconnected");
}

void Serial::readSerial()
{
    const QByteArray data = this->readAll();

    inData->append(QString::fromUtf8(data));

    while(inData->contains('\n') || inData->contains('\r'))
    {
        int i;
        if(inData->contains('\n'))
        {
            inData->remove('\r');
            i = inData->indexOf('\n');
        }
        else
            i = inData->indexOf('\r');

        if(inData->at(0) == 'e' || inData->at(0) == '~')
        {
            writeSerial("ok\n");
        }
        else if(inData->at(0) == '?' && inData->at(1) == 'h')
        {
            this->write("ok\n");
            //m_parent->serialLogEntry->addLine("ok");
        }
        else if(inData->at(0) == '!')
        {
            if(inData->at(1) == 'C' && !overC)
            {
                overC = true;
                //m_parent->splash->showText("Overcurrent detected!");
            }
            else if(inData->at(1) == 'V' && !overV)
            {
                overV = true;
                //m_parent->splash->showText("Overvoltage detected!");
            }
            else if(inData->at(1) == 'T' && !overT)
            {
                overT = true;
                //m_parent->splash->showText("Overtemperature detected!");
            }
            else if(inData->at(1) == 'v' && !underV)
            {
                underV = true;
                //m_parent->splash->showText("Low voltage detected!");
            }
        }
        else if(inData->at(0) == 'u' && inData->at(1) == 'p')
        {
            emit motorIsUp();
            overT = false;
            overV = false;
            overC = false;
            underV = false;
        }
        else if(inData->at(0) == 's' && inData->at(1) == 'h')
        {
            emit motorIsShut();
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
                QString entryNum = inData->mid(1,inData->indexOf('-')-1);
                dataEntry = entryNum.toInt();
                if(inData->mid(inData->indexOf('-')+1,i-inData->indexOf('-')-1) != "257.0")
                    display(inData->mid(inData->indexOf('-')+1,i-inData->indexOf('-')-1));
                else
                    display("CRC");
            }
        }
        else
        {
            // Unknown data
        }
        //m_parent->serialLogEntry->addLine(inData->left(i));
        *inData = inData->remove(0,i+1);

    }
}


void Serial::writeSerial(const QByteArray &outData)
{
    this->write(outData);
    QByteArray temp = outData;
    temp.chop(1);
    //m_parent->serialLogEntry->addLine(temp + " ------->");
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
        //QMessageBox::critical(this, "Critical Error", m_serial->errorString());
        //m_parent->splash->showText("Serial port error!");
        //m_parent->errorsEntry->addLine("Serial port error - "+m_serial->errorString());
        closeSerialPort();
    }
}


