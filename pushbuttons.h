#ifndef PUSHBUTTONS_H
#define PUSHBUTTONS_H


#if RPI

#include <QObject>
#include <QThread>
#include <QTimer>

#include "menu.h"
#include "wiringPi.h"

class MainWindow;

class PushButtons : public QObject
{
    Q_OBJECT

public:
    PushButtons(MainWindow *parent);

    static void isrCatchR();
    static void isrCatchL();
    static PushButtons *isrClass;

public slots:
    void switchL();
    void switchR();

signals:

private:
    MainWindow *m_parent;

    bool lActive = false;
    bool rActive = false;
    bool rHeld = false;
    int debounceTime = 50;

    QTimer *holdTimer = new QTimer;
    QTimer *timerL = new QTimer;
    QTimer *timerR = new QTimer;
    Menu *menu = nullptr;

private slots:
    void closeMenu();
};
#endif

#endif // PUSHBUTTONS_H
