#include "clock.h"

Clock::Clock()
{
    QFont font("Digital-7 Mono", 40, Qt::white);

    time = time.currentTime();
    this->setText(time.toString("hh:mm"));
    this->setFont(font);
    this->setStyleSheet("QLabel {color: white;}");
    this->setMargin(10);

    updateInterval->setSingleShot(false);
    updateInterval->setInterval(2000);
    updateInterval->start();

    connect(updateInterval, SIGNAL(timeout()),
            this, SLOT(changeTime()));
}

void Clock::changeTime()
{
    time = time.currentTime();
    this->setText(time.toString("hh:mm"));
}
