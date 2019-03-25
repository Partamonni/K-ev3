#include "meterbar.h"
#include "mainwindow.h"

#include <QWidget>

Meterbar::Meterbar()
{
    this->setLayout(meterLay);
    this->setFixedSize(SCR_WIDTH, SCR_HEIGHT);

    font->setLetterSpacing(QFont::PercentageSpacing, 90);
    font->setFamily("Digital-7 Mono");
    font->setPixelSize(90);
    font->setCapitalization(QFont::AllUppercase);
    font->setWeight(QFont::Bold);

    amps->setFont(*font);
    amps->setText("0");
    amps->setStyleSheet("color: white;");

    ampsUnit->setFont(*font);
    ampsUnit->setText("A");
    ampsUnit->setStyleSheet("color: white;");

    volts->setFont(*font);
    volts->setText("0");
    volts->setStyleSheet("color: white;");

    voltsUnit->setFont(*font);
    voltsUnit->setText("V");
    voltsUnit->setStyleSheet("color: white;");

    fillLabel->setFixedSize(SCR_WIDTH, font->pixelSize());
    fill->fill(QColor(0,0,0,230));
    fill->scaled(SCR_WIDTH, font->pixelSize());
    fillLabel->setPixmap(*fill);

    meterLay->addWidget(fillLabel,1,1,1,3);
    meterLay->addWidget(volts,1,2,Qt::AlignRight);
    meterLay->addWidget(voltsUnit,1,3,Qt::AlignLeft);
    meterLay->addWidget(amps,1,4,Qt::AlignRight);
    meterLay->addWidget(ampsUnit,1,5,Qt::AlignLeft);
    meterLay->setVerticalSpacing(0);
    meterLay->setHorizontalSpacing(5);
    meterLay->setContentsMargins(0,0,10,0);

    this->show();
}
