#include "menu.h"
#include "mainwindow.h"

#include <QPoint>
#include <QPropertyAnimation>
#include "mainwindow.h"

Menu::Menu(MainWindow *parent)
{
    this->setFixedSize(SCR_WIDTH/4, SCR_HEIGHT);

    // Initialize render pixmap size
    menuRender = new QPixmap(this->size());

    this->setLayout(bgLayout);
    bgLayout->setContentsMargins(0,0,0,0);
    bgLayout->addWidget(menuFrame);
    menuFrame->setLayout(layout);

    selectorImg->load(":/btnsel");
    selector->setPixmap(*selectorImg);
    selector->setPixmap(selectorImg->scaled(SCR_WIDTH/4,SCR_HEIGHT/btnCount));
    selectorHeight = SCR_HEIGHT/btnCount;

    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(selector,0,0);

    this->hide();

    motEffMen->setEasingCurve(QEasingCurve::InOutQuad);
    motEffMen->setDuration(500);

    motEffSel->setEasingCurve(QEasingCurve::OutQuint);
    motEffSel->setDuration(300);

    connect(motEffMen, &QPropertyAnimation::finished, this, &Menu::hideMenu);
}

void Menu::toggleSelector()
{
    if(motEffSel->state() == QPropertyAnimation::Running)
        motEffSel->stop();

    motEffSel->setStartValue(QPoint(0, selPos * selectorHeight));
    if(++selPos >= btnCount) // Increase by one, 0 if goes over bounds
        selPos = 0;
    motEffSel->setEndValue(QPoint(0, selPos * selectorHeight));
    motEffSel->start();
}

void Menu::addButton(QPushButton *btn)
{
    layout->addWidget(btn, btnsInserted, 0);
    btnsInserted++;
}

int Menu::buttonCount()
{
    return btnCount;
}

// For functionality, see class Entry.

void Menu::openMenu()
{
    menuFrame->show();
    this->render(menuRender);
    this->setPixmap(*menuRender);

    motEffMen->setDirection(QPropertyAnimation::Forward);
    motEffMen->setStartValue(QPoint(0,-this->height()));
    motEffMen->setEndValue(QPoint(0,0));
    menuFrame->hide();
    this->show();

    motEffMen->start();
    menuOpen = true;
}

void Menu::closeMenu()
{
    if(menuOpen)
    {
        this->render(menuRender);
        this->setPixmap(*menuRender);
        motEffMen->setEndValue(this->pos());
        motEffMen->setDirection(QPropertyAnimation::Backward);
        menuFrame->hide();
        motEffMen->start();
        menuOpen = false;
        selPos = 0;
        emit menuClosing();
    }
}

void Menu::hideMenu()
{
    if(!menuOpen)
    {
        this->hide();
        emit justClosed();
        selector->setGeometry(QRect(QPoint(0,0), selector->size()));
    }
    else
    {
        menuFrame->show();
    }
}


int Menu::selectorPosition()
{
    return selPos;
}

bool Menu::isClosing()
{
    if(motEffMen->state() == QPropertyAnimation::Running &&
            motEffMen->direction() == QPropertyAnimation::Backward)
        return true;
    else
        return false;
}

bool Menu::isOpen()
{
    return menuOpen;
}
