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
#include "entryerrors.h"
#include "entrymotor.h"
#include "entryseriallog.h"
#include "entrystats.h"
#include "entrystatus.h"
#include "entrytemp.h"
#include "clock.h"

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
    void lPressEvent1();
    void lPressEvent2();
    void rPressEvent();
    void kPressEvent();

#if !RPI
protected:
    void mouseReleaseEvent(QMouseEvent *mouseEvent1);
    void mousePressEvent(QMouseEvent *mouseEvent2);
    void keyPressEvent(QKeyEvent *keyEvent);
#endif
private:

    void (Entry::*toggleEntryFunc)() = nullptr;
    bool entryOpen = false;

    QWidget *center = new QWidget;
    QGridLayout *bgLayout = new QGridLayout;
    QLabel *bgLabel = new QLabel;
    QPixmap *bgImg = new QPixmap;

    QLabel *fgFrame = new QLabel;
    QGridLayout *fgLayout = new QGridLayout;
    QGraphicsOpacityEffect *opaEff = new QGraphicsOpacityEffect;

    Meterbar *meter = new Meterbar;
    Menu *menu = new Menu;
    Serial *serial = new Serial(this);

    Entry **entries = nullptr;
    Entry *closingEntry = nullptr;
    EntryTemp *entryTemp = new EntryTemp(this);
    EntryStatus *entryStatus= new EntryStatus(this);
    EntryStats *entryStats= new EntryStats(this);
    EntrySerialLog *entrySerialLog = new EntrySerialLog(this);
    EntryErrors *entryErrors = new EntryErrors(this);
    EntryMotor *entryMotor= new EntryMotor(this);

    Clock *clock = new Clock;

    //PushButtons *pushButtons = new PushButtons(this);

    friend class PushButtons;
    friend class Serial;
};

#endif // MAINWINDOW_H
