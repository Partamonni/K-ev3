#include "pushbuttons.h"

#include <QTime>
#include <QTimer>
#include <QCoreApplication>

#include "mainwindow.h"
#include "wiringPi.h"

#define output33 1
#define inputL 26
#define inputR 27

#if RPI


PushButtons::PushButtons(MainWindow *parent)
{
    isrClass = this;
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
}


void PushButtons::isrCatchL()
{
    if(!isrClass->lActive)
    { // If pressed, ignore bounces and start debounce timer
        isrClass->lActive = true;
        if(!digitalRead(inputL) && !isrClass->holdTimer->isActive())
            isrClass->timerL->start();
        else if(isrClass->holdTimer->isActive())
        {   // If button wasn't held long enough, it was typical press.
            isrClass->holdTimer->stop();
            isrClass->menu->toggleSelector();
            isrClass->lActive = false;
        } // If the press didn't last the debounce, just reset lActive flag

    }
}

void PushButtons::isrCatchR()
{
    if(!isrClass->rActive)
    {
        isrClass->rActive = true;
        if(!digitalRead(inputR))
            isrClass->timerR->start();
        else if(isrClass->rHeld)
        {
            //isrClass->menu->toggleEntry(); HOX!
        }
    }
}

void PushButtons::switchL()
{
    if(!digitalRead(inputL)) // If button is really pressed
    {
        holdTimer->start();
    }   // return to wait release
    lActive = false;
}

void PushButtons::switchR()
{
    if(!digitalRead(inputR))
    {   // If button is really pressed
        // menu->toggleEntry(); HOX!
        rHeld = true;
    }   // Return to wait release
    rActive = false;
}

void PushButtons::closeMenu()
{
    menu->closeMenu();
}
#endif
