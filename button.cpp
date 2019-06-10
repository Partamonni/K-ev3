#include "mainwindow.h"
#include "button.h"
#include "menu.h"

Button::Button(Menu *parent, QString text)
{
    QFont font;
    font.setFamily("Square Sans Serif 7");
    font.setPixelSize(20);
    font.setCapitalization(QFont::AllUppercase);
    font.setLetterSpacing(QFont::PercentageSpacing, 110);
    font.setStretch(75);

    button->setText(text);
    button->setFixedSize(SCR_WIDTH/4,SCR_HEIGHT/parent->buttonCount());
    button->setFont(font);
    button->setStyleSheet("QPushButton {border-image: url(:/btn); color: white;}");

    parent->addButton(button);
}

void Button::setText(QString text)
{
    button->setText(text);
}
