#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QBoxLayout>
#include <QFont>
#include <QPropertyAnimation>

#include "button.h"

class MainWindow;

class Menu : public QWidget
{
    Q_OBJECT

public:
    Menu(MainWindow *parent = nullptr);
    ~Menu();

    void addButton(QPushButton *btn);
    int selectorPosition();
    int buttonCount();
    int entryCount();

public slots:
    void toggleSelector();
    void openMenu();
    void closeMenu();

private:
    int selPos = 0;
    int btnCount = 6;
    int btnsInserted = 0;
    int selectorHeight;
    bool entryOpen = false;
    bool menuOpen = false;
    int holdReleaseTime = 600;

    QLabel *selector = new QLabel;
    QPixmap *selectorImg = new QPixmap;
    QGridLayout *layout = new QGridLayout;

    Button *btn0 = new Button(this, "Temperatures");
    Button *btn1 = new Button(this, "Status");
    Button *btn2 = new Button(this, "Stats");
    Button *btn3 = new Button(this, "Serial Log");
    Button *btn4 = new Button(this, "Errors");
    Button *btn5 = new Button(this, "Motor Power\nOn");

    QPropertyAnimation *motEffMen = new QPropertyAnimation(this, "pos"); // motion effect for menu
    QPropertyAnimation *motEffSel = new QPropertyAnimation(selector, "pos"); // motion effect for selector

    friend class PushButtons;
private slots:
    void hideMenu();

};

#endif // MENU_H
