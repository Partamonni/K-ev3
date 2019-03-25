#include "menu.h"
#include "mainwindow.h"

#include <QPoint>
#include <QPropertyAnimation>
#include "mainwindow.h"

Menu::Menu(MainWindow *parent)
{
    this->setLayout(layout);
    this->setFixedSize(SCR_WIDTH/4, SCR_HEIGHT);

    selectorImg->load(":/btnsel");
    selector->setPixmap(*selectorImg);
    selector->setPixmap(selectorImg->scaled(SCR_WIDTH/4,SCR_HEIGHT/btnCount));
    selectorHeight = SCR_HEIGHT/btnCount;

    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(selector,0,0);

    motEffMen->setEasingCurve(QEasingCurve::InOutQuad);
    motEffMen->setDuration(600);

    motEffSel->setEasingCurve(QEasingCurve::OutQuint);
    motEffSel->setDuration(300);

    this->hide();
    connect(motEffMen, &QPropertyAnimation::finished, this, &Menu::hideMenu);
}

Menu::~Menu()
{

}

void Menu::toggleSelector()
{
    if(motEffSel->state() == QPropertyAnimation::Running)
        motEffSel->stop();

    motEffSel->setStartValue(QPoint(0, selPos * selectorHeight));
    if(++selPos >= btnCount)
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
{return btnCount;}

void Menu::closeMenu()
{
    if(menuOpen)
    {
        motEffMen->setEndValue(this->pos());
        motEffMen->setDirection(QPropertyAnimation::Backward);
        motEffMen->start();
        menuOpen = false;
    }
}

void Menu::openMenu()
{
    motEffMen->setDirection(QPropertyAnimation::Forward);
    motEffMen->setStartValue(QPoint(0,-this->height()));
    motEffMen->setEndValue(QPoint(0,0));
    motEffMen->start();
    menuOpen = true;
    this->show();
}

void Menu::hideMenu()
{
    if(!menuOpen)
    {
        this->hide();
    }
}


int Menu::selectorPosition()
{
    return selPos;
}
