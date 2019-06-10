#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>


/* These buttons are rather some dummy labels at the end of the design.
 * Reason is that it was during the writing to call the openable objects
 * directly from the function that controls their function.
 */

class Menu;

class Button : public QWidget
{
    Q_OBJECT

public:
    Button(Menu *parent = nullptr, QString text = nullptr);

    void setText(QString text);

private:
    QPushButton *button = new QPushButton;
};

#endif // BUTTON_H
