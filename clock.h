#ifndef CLOCK_H
#define CLOCK_H

#include <QLabel>
#include <QTimer>
#include <QTime>

/* Simple clock that displays system time on upper right corner. Updates once per sec. */

class Clock : public QLabel
{
    Q_OBJECT
public:
    Clock();

private slots:
    void changeTime();

private:
    QTime time;
    QTimer *updateInterval = new QTimer;
};

#endif // CLOCK_H
