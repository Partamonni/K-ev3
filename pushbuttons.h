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

public slots:
    void switchL();
    void switchR();

signals:
    void signalL();
    void signalR();

private:
    MainWindow *m_parent;

    bool lActive = false;
    bool rActive = false;
    bool lBouncing = false;
    bool rBouncing = false;
    bool lDown = false;
    int debounceTime = 50;

    QTimer *holdTimer = new QTimer(this);
    QTimer *timerL = new QTimer(this);
    QTimer *timerR = new QTimer(this);
    Menu *menu = nullptr;

private slots:
    void closeMenu();
};
#endif

#endif // PUSHBUTTONS_H
