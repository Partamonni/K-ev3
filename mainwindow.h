#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QGraphicsOpacityEffect>
#include <QTime>
#include <QTimer>

#include "meterbar.h"
#include "menu.h"
#include "serial.h"
#include "pushbuttons.h"
#include "entry.h"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;

#define RPI 0

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void toggleEntry();
    void toggleMotorEntry();

signals:
    void lPressEvent();
    void lReleaseEvent();
    void rPressEvent();

#if !RPI
protected:
    void mouseReleaseEvent(QMouseEvent *mouseEvent1);
    void mousePressEvent(QMouseEvent *mouseEvent2);
    void keyPressEvent(QKeyEvent *keyEvent);
#endif
private:

    QWidget *center = new QWidget;
    QGridLayout *bgLayout = new QGridLayout;
    QLabel *bgLabel = new QLabel;
    QPixmap *bgImg = new QPixmap;

    QGridLayout *fgLayout = new QGridLayout;

    Meterbar *meter = new Meterbar;
    Menu *menu = new Menu;
    Serial *serial = new Serial(this);

    Entry **entries = nullptr;
    Entry *closingEntry = nullptr;
    Entry *testEntry = new Entry(this);
    //PushButtons *pushButtons = new PushButtons(this);

    void (Entry::*lastEntryFunc)() = nullptr;

    friend class PushButtons;
    friend class Serial;
};

#endif // MAINWINDOW_H
