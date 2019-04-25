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
#include "notice.h"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void toggleEntry();

#if !RPI
signals:
    void lPressEvent1();
    void lPressEvent2();
    void rPressEvent();
    void kPressEvent();
#endif

private:
#if !RPI
    void mouseReleaseEvent(QMouseEvent *mouseEvent1);
    void keyPressEvent(QKeyEvent *keyEvent);
#endif

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
    Notice *notice = new Notice;
#if RPI
    PushButtons *pushButtons = new PushButtons(this);
#endif
    friend class PushButtons;
    friend class Serial;
};

#endif // MAINWINDOW_H
