#include "entry.h"

#include <QGraphicsBlurEffect>
#include "mainwindow.h"

Entry::Entry(MainWindow *parent)
{
    m_parent = parent;
    entWidth = SCR_WIDTH*3/4;

    entryRender = new QPixmap(this->size()); // Initialize pixmap size

    this->setLayout(bgLayout);
    bgLayout->setContentsMargins(0,0,0,0);
    bgLayout->addWidget(entryFrame);
    entryFrame->setLayout(entryLayout);

    QFont font("Digital-7 Mono", 28, Qt::white);
    this->setFont(font);
    this->setStyleSheet("QLabel {color: white;}");
    this->setFixedSize(entWidth, SCR_HEIGHT);

    // Load and scale bg image
    entryBg->load(":/entrybg");
    *entryBg = entryBg->scaled(this->size(),
                        Qt::IgnoreAspectRatio,
                        Qt::SmoothTransformation);
    this->setFixedSize(entWidth, SCR_HEIGHT);
    this->setPixmap(*entryBg);
    entryLayout->setContentsMargins(0,0,0,0);
    entryLayout->setSpacing(0);

    this->hide();

    motEffEntry->setEasingCurve(QEasingCurve::InSine);
    motEffEntry->setDuration(500);

    connect(motEffEntry, &QPropertyAnimation::finished, this, &Entry::hideEntry);
}

/* With animations, widget is first rendered to a pixmap.
 * The frame holding the content is then hidden and the rendered picture
 * is displayed in base widgets background. This widget is then animated.
 *
 * After animation, normal background is returned and content frame shown again.
 *
 * This improves performance because already jittering position animations
 * jitters even more when widget has layouts with other widgets in it.
 * Also, leaving content in place shows a brief flicker of content before hiding
 * after the animation, so this gets rid of that too.
 *
 * More elegant solution would have been QML animations, which use openGL rendering
 * instead of native windowing system API, but for this application this suffices.
 */

void Entry::toggleEntry()
{
    if(!entryOpen)
    {
        entryFrame->show();
        this->render(entryRender);
        this->setPixmap(*entryRender);

        motEffEntry->setDirection(QPropertyAnimation::Forward);
        motEffEntry->setStartValue(QPoint(SCR_WIDTH,0));
        motEffEntry->setEndValue(QPoint(SCR_WIDTH/4,0));
        entryFrame->hide();
        this->show();
        this->raise();
        motEffEntry->start();
        entryOpen = true;
    }
    else
    {
        this->render(entryRender);
        this->setPixmap(*entryRender);

        if(motEffEntry->state() == QPropertyAnimation::Running)
        {
            motEffEntry->stop();
            motEffEntry->setEndValue(this->pos());
        }

        motEffEntry->setDirection(QPropertyAnimation::Backward);
        entryFrame->hide();
        motEffEntry->start();
        entryOpen = false;
    }
}

void Entry::hideEntry()
{
    if(!entryOpen)
    {
        this->hide();
    }
    else
    {
        this->setPixmap(*entryBg);
        entryFrame->show();
    }
}

bool Entry::isClosing()
{
    if(motEffEntry->state() == QPropertyAnimation::Running)
        return true;
    else
        return false;
}

bool Entry::hidesPrevious(){return hidePrevious;}
