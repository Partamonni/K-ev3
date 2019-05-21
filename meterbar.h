#ifndef METERBAR_H
#define METERBAR_H

#include <QWidget>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QGridLayout>

extern int SCR_WIDTH;
extern int SCR_HEIGHT;

class Meterbar : public QWidget
{
    Q_OBJECT

public:
    Meterbar();

public slots:
    void setAmp(QString amp){ amps->setText(amp); }
    void setVolt(QString volt){ volts->setText(volt); }

private:
    QWidget *meterFrame = new QWidget;
    QGridLayout *meterLay = new QGridLayout;

    QPixmap *fill = new QPixmap(SCR_WIDTH,SCR_HEIGHT);
    QLabel *fillLabel = new QLabel(this);

    QLabel *amps = new QLabel;
    QLabel *ampsUnit = new QLabel;
    QLabel *volts = new QLabel;
    QLabel *voltsUnit = new QLabel;
    QFont *font = new QFont;
};

#endif // METERBAR_H
