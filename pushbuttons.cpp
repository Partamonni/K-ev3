#include "pushbuttons.h"

#include <QTime>
#include <QTimer>
#include <QCoreApplication>

#include "mainwindow.h"
#include "wiringPi.h"
#include "notice.h"

#define output33 1
// This is voltage source to go along with the physical serial wires

#define inputL 26
#define inputR 27

#if RPI

PushButtons::PushButtons(MainWindow *parent)
{
    // Set this object to be the class for the physical buttons
    isrObject = this;
    wiringPiSetup(); // Initialize wiringPi
    m_parent = parent;
    menu = m_parent->menu; // Pointer to simplify code
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

// These must-be-static functions catch wiringPi ISR
void PushButtons::isrCatchL()
{
    if(!isrObject->lActive)
    {
        isrObject->lActive = true;
        emit isrObject->signalL();
        // To start timers in other threads, one must use signals & slots
    }
}

void PushButtons::isrCatchR()
{
    if(!isrObject->rActive)
    {
        isrObject->rActive = true;
        emit isrObject->signalR();
    }
}

void PushButtons::switchL()
{
    if(!lDown) // The button is being pressed
    {
        if(!lBouncing && !digitalRead(inputL)) // Bouncing
        {
            timerL->start();
            lBouncing = true;
            // This timer returns to this function after timeout
            // with lBouncing == true
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
            lActive = false; // If the press wasn't good enough
    }
    else // The button is being released
    {
        if(!lBouncing && digitalRead(inputL)) // Bouncing
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
            lActive = false; // If the release didn't happen
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
