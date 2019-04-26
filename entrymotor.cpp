#include "entrymotor.h"
#include "notice.h"
#include "mainwindow.h"

EntryMotor::EntryMotor(MainWindow *parent)
{
    hidePrevious = false;
}

void EntryMotor::toggleEntry()
{
    if(serial != nullptr)
    {
        if(!powerEnabled)
        {
            serial->writeSerial("ok\n");
            Notice::showText("Power enabled!");
        }
        else
        {
            serial->writeSerial("!S\n");
            Notice::showText("Power disabled!");
        }
    }
    else
    {
        Notice::showText("Serial not set!");
        //m_parent->entryErrors
    }
}

void EntryMotor::setSerial(Serial *serialObject)
{
    serial = serialObject;
}
