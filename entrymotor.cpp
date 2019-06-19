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

    connect(timer, &QTimer::timeout, this, &EntryMotor::retry);
}

void EntryMotor::toggleEntry()
{
    if(serial != nullptr)
    {
        if(!timer->isActive())
        {
            timer->start(waitForActionTime/10);

            if(!powerOn)
            {
                powerWanted = true;
                serial->writeSerial("ok\n");
            }
            else
            {
                powerWanted = false;
                serial->writeSerial("!S\n");
            }
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

void EntryMotor::command(bool isShut)
{
    powerOn = !isShut;
    if(powerWanted == powerOn)
    {
        timer->stop();
        retries = 0;
    }
}

void EntryMotor::retry()
{
    if(!powerOn)
    {
        powerWanted = true;
        serial->writeSerial("ok\n");
    }
    else
    {
        powerWanted = false;
        serial->writeSerial("!S\n");
    }

    if(retries++ >= 10)
    {
        if(powerWanted)
        {
            powerOn = false;
            powerWanted = false; // We don't want the motor suddenly coming alive
            Notice::showText("Module didn\'t answer!\nPower up failed!");
        }
        else
        {
            powerOn = true;
            Notice::showText("Module didn\'t answer!\nPower down failed!");
        }
        timer->stop();
        retries = 0;
        EntryErrors::addLine("Power Module didn't answer in time!");
    }
}
