#include "entry.h"

#include <QGraphicsBlurEffect>

extern short int SCR_WIDTH;
extern short int SCR_HEIGHT;

Entry::Entry(MainWindow *parent)
{
    m_parent = parent;
    entWidth = SCR_WIDTH*3/4;
    QFont font("Digital-7 Mono", 28, Qt::white);

    motEffEntry->setEasingCurve(QEasingCurve::InSine);
    motEffEntry->setDuration(800);

    this->setFont(font);
    this->setStyleSheet("QLabel {color: white;}");
    this->setFixedSize(entWidth, SCR_HEIGHT);
    this->setLayout(entryLayout);

    entryBg->load(":/entrybg");
    canvas->setFixedSize(entWidth, SCR_HEIGHT);
    canvas->setPixmap(entryBg->scaled(canvas->size(),
                                      Qt::IgnoreAspectRatio,
                                      Qt::SmoothTransformation));
    canvas->setGraphicsEffect(new QGraphicsBlurEffect());
    entryLayout->addWidget(canvas,0,0);
    entryLayout->setContentsMargins(0,0,0,0);
    entryLayout->setSpacing(0);
    this->hide();

    connect(motEffEntry, &QPropertyAnimation::finished, this, &Entry::hideEntry);
}

void Entry::toggleEntry()
{
    if(!entryOpen)
    {
        motEffEntry->setDirection(QPropertyAnimation::Forward);
        motEffEntry->setStartValue(QPoint(SCR_WIDTH,0));
        motEffEntry->setEndValue(QPoint(SCR_WIDTH/4,0));
        motEffEntry->start();
        this->raise();
        entryOpen = true;
        this->show();
    }
    else
    {
        if(motEffEntry->state() == QPropertyAnimation::Running)
        {
            motEffEntry->stop();
            motEffEntry->setEndValue(this->pos());
        }
        motEffEntry->setDirection(QPropertyAnimation::Backward);
        motEffEntry->start();
        entryOpen = false;
    }
}

void Entry::hideEntry()
{
    if(!entryOpen)
        this->hide();
}

bool Entry::isClosing()
{
    if(motEffEntry->state() == QPropertyAnimation::Running)
        return true;
    else
        return false;
}
