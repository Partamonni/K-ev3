#include "entrymotor.h"
#include "notice.h"
#include "mainwindow.h"

#include <QTimer>
#include <QLabel>

/* This class doesn't open visible entry, instead it sends
 * command through a serial port.
 */

EntryMotor::EntryMotor(MainWindow *parent)
{
    hidePrevious = false;
    timer->setSingleShot(false);
    // Default timer for this entry is reused in serial send retry context

    connect(timer, &QTimer::timeout, this, &EntryMotor::alertFailure);
}

void EntryMotor::toggleEntry()
{
    if(serial != nullptr)
    {
        timer->start(100);

        if(!powerEnabled)
        {
            serial->writeSerial("ok\n");
        }
        else
        {
            serial->writeSerial("!S\n");
        }
    }
    else
    {
        Notice::showText("Serial not set!");
        EntryErrors::addLine("Serial wasn't open - Couldn't command motor");
    }
}

void EntryMotor::setSerial(Serial *serialObject)
{
    // Set pointer for easier addressing of the serial class
    serial = serialObject;
}

void EntryMotor::success(bool isShut)
{
    timer->stop();
    retries = 0;
    powerEnabled = !isShut;
}

void EntryMotor::alertFailure()
{
    if(retries++ >= 10)
    {
        if(!powerEnabled)
            Notice::showText("Module didn\'t answer!\nPower up failed!");
        else
            Notice::showText("Module didn\'t answer!\nPower down failed!");
        timer->stop();
        retries = 0;
        EntryErrors::addLine("Power Module didn't answer in time!");
    }
}
