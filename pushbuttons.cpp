#include "pushbuttons.h"

#include <QTime>
#include <QTimer>
#include <QCoreApplication>

#include "mainwindow.h"
#include "wiringPi.h"
#include "notice.h"

#define output33 1
#define inputL 26
#define inputR 27

#if RPI

PushButtons::PushButtons(MainWindow *parent)
{
    isrObject = this;
    wiringPiSetup();
    m_parent = parent;
    menu = m_parent->menu;
    pinMode(output33, OUTPUT);
    digitalWrite(output33, 1);

    pinMode(inputL, INPUT);
    pinMode(inputR, INPUT);
    pullUpDnControl(inputL, PUD_UP);
    pullUpDnControl(inputR, PUD_UP);

    timerL->setSingleShot(true);
    timerL->setInterval(debounceTime);
    timerR->setSingleShot(true);
    timerR->setInterval(debounceTime);
    holdTimer->setSingleShot(true);
    holdTimer->setInterval(menu->holdReleaseTime);

    wiringPiISR(inputL, INT_EDGE_BOTH, isrCatchL);
    wiringPiISR(inputR, INT_EDGE_BOTH, isrCatchR);

    connect(timerL, &QTimer::timeout, this, &PushButtons::switchL);
    connect(timerR, &QTimer::timeout, this, &PushButtons::switchR);
    connect(holdTimer, &QTimer::timeout, this, &PushButtons::closeMenu);
    connect(this, &PushButtons::signalL, this, &PushButtons::switchL);
    connect(this, &PushButtons::signalR, this, &PushButtons::switchR);
}


void PushButtons::isrCatchL()
{
    /*if(!isrObject->lActive)
    { // If pressed, ignore bounces and start debounce timer
        isrObject->lActive = true;
        if(!digitalRead(inputL) && !isrObject->holdTimer->isActive())
            isrObject->timerL->start();
        else if(isrObject->holdTimer->isActive())
        {   // If button wasn't held long enough, it was typical press.
            isrObject->holdTimer->stop();
            isrObject->menu->toggleSelector();
            isrObject->lActive = false;
        }
    }*/
    if(!isrObject->lActive)
    {
        isrObject->lActive = true;
        emit isrObject->signalL();
    }
}

void PushButtons::isrCatchR()
{
    /*if(!isrObject->rActive)
    {
        isrObject->rActive = true;
        if(!digitalRead(inputR))
            isrObject->timerR->start();
        else if(isrObject->rHeld)
        {
            isrObject->m_parent->toggleEntry();
        }
    }*/
    if(!isrObject->rActive)
    {
        isrObject->rActive = true;
        emit isrObject->signalR();
    }
}

void PushButtons::switchL()
{
    if(!lDown)
    {
        if(!lBouncing && !digitalRead(inputL))
        {
            timerL->start();
            lBouncing = true;
        }
        else if(lBouncing && !digitalRead(inputL))
        {
            lBouncing = false;
            lDown = true;
            if(menu->isOpen())
                holdTimer->start();
            else
                menu->openMenu();
            lActive = false;
        }   // return to wait release
        else
            lActive = false;
    }
    else
    {
        if(!lBouncing && digitalRead(inputL))
        {
            timerL->start();
            lBouncing = true;
        }
        else if(lBouncing && digitalRead(inputL))
        {
            lBouncing = false;
            if(holdTimer->isActive())
            {   // If button wasn't held long enough, it was typical press.
                holdTimer->stop();
                menu->toggleSelector();
            }
            lDown = false;
            lActive = false;
        }
        else
            lActive = false;
    }
}

void PushButtons::switchR()
{
    if(!rBouncing && !digitalRead(inputR))
    {
        timerR->start();
        rBouncing = true;
    }
    else if(rBouncing && !digitalRead(inputR))
    {
        m_parent->toggleEntry();
        rActive = false;
    }
    else
        rActive = false;
}

void PushButtons::closeMenu()
{
    menu->closeMenu();
}
#endif
