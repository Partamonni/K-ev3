#include "entrymotor.h"
#include "notice.h"
#include "mainwindow.h"

#include <QTimer>
#include <QLabel>

EntryMotor::EntryMotor(MainWindow *parent)
{
    hidePrevious = false;
    timer->setSingleShot(false);

    connect(timer, &QTimer::timeout, this, &EntryMotor::alertFailure);
}

void EntryMotor::toggleEntry()
{
    if(serial != nullptr)
    {
        stateChangeSuccess = false;
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
        EntryErrors::addLine("Serial wasn't open - Couldn't power motor");
    }
}

void EntryMotor::setSerial(Serial *serialObject)
{
    serial = serialObject;
}

void EntryMotor::success()
{
    timer->stop();
    retries = 0;
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
