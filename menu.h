#ifndef MENU_H
#define MENU_H

/* Animated menu widget, contains button labels and the selector.
 */

#include <QLabel>
#include <QBoxLayout>
#include <QFont>
#include <QPropertyAnimation>

#include "button.h"

class MainWindow;

class Menu : public QLabel
{
    Q_OBJECT

public:
    Menu(MainWindow *parent = nullptr);

    void addButton(QPushButton *btn);
    int selectorPosition();
    int buttonCount();
    int entryCount();
    bool isClosing();
    bool isOpen();

public slots:
    void toggleSelector();
    void openMenu();
    void closeMenu();
    void setMotorText(QString text);

signals:
    void menuClosing();
    void justClosed();

private:
    int selPos = 0;
    int btnCount = 5;
    int btnsInserted = 0;
    int selectorHeight = 0;
    bool menuOpen = false;
    int holdReleaseTime = 600;

    QLabel *selector = new QLabel;
    QPixmap *selectorImg = new QPixmap;
    QPixmap *menuRender;
    QGridLayout *layout = new QGridLayout;
    QGridLayout *bgLayout = new QGridLayout;
    QWidget *menuFrame = new QWidget;

    Button *btn0 = new Button(this, "Temperatures");
    Button *btn1 = new Button(this, "Status");
    //Button *btn2 = new Button(this, "Stats");
    Button *btn3 = new Button(this, "Serial Log");
    Button *btn4 = new Button(this, "Errors");
    Button *btn5 = new Button(this, "Motor Power\nOn");

    QPropertyAnimation *motEffMen = new QPropertyAnimation(this, "pos");
    QPropertyAnimation *motEffSel = new QPropertyAnimation(selector, "pos");

    friend class PushButtons;
private slots:
    void hideMenu();

};

#endif // MENU_H
