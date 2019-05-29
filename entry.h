#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTimer>

/* Animated superclass to provide common functionality for all the entries.
 * Provides basically as itself a working template to which add information.
*/

class MainWindow;

class Entry : public QLabel
{
    Q_OBJECT
public:
    Entry(MainWindow *parent = nullptr);
    bool isClosing();
    bool hidesPrevious();

signals:

public slots:
    virtual void toggleEntry();

protected:
    QGridLayout *entryLayout = new QGridLayout;
    QGridLayout *bgLayout = new QGridLayout;
    QPixmap *entryBg = new QPixmap;
    QPixmap *entryRender = nullptr;
    QWidget *entryFrame = new QWidget;
    QTimer *timer = new QTimer;
    QPropertyAnimation *motEffEntry = new QPropertyAnimation(this, "pos");
    MainWindow *m_parent = nullptr;

    /* Basic structure of an entry is described below:
     *
     *  this (contains background and during animations the rendered image of a last state)
     *  |
     *  bgLayout
     *  |
     *  entryFrame (this is widget that is toggles off during animations to improve performance)
     *  |
     *  entryLayout (this is where the entry content is placed)
     */

    bool hidePrevious = true; // Only entry to use this is motor power toggle, that doesn't open a visual entry.

private:
    int entWidth = 0;
    bool entryOpen = false;

private slots:
    void hideEntry();
};
#endif // ENTRY_H
