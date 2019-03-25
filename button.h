#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>

class Menu;

class Button : public QWidget
{
    Q_OBJECT

public:
    Button(Menu *parent = nullptr, QString text = nullptr);

    QPushButton *button = new QPushButton;
};

#endif // BUTTON_H
