#include "entrytemp.h"
#include "mainwindow.h"

#include <QLabel>
#include <math.h>

EntryTemp::EntryTemp(MainWindow *parent)
{
    int columns = 4;
    int initCount = 40;

    for (int i = 0; i < initCount; ++i)
    {
        packTemp[i] = new QLabel;
        packTemp[i]->setFont(this->font());
        packTemp[i]->setStyleSheet("QLabel {background-color: rgba(0,0,0,80); color: white;}");
    }

    entryLayout->addLayout(grid,0,0);
    grid->setContentsMargins(15,20,15,20);

    int rows;
    do
    {
        double a = initCount;
        double b = columns;
        double rowsTmp = a/b;
        rows = static_cast<int>(ceil(rowsTmp));
    }
    while(false);

    for(int i = 0; i < initCount; ++i)
    {
        static int col = 0;

        if (i % rows == 0 && i != 0)
            ++col;

        grid->addWidget(packTemp[i],i-(col*rows),col,Qt::AlignCenter);
        packTemp[i]->setText((QString("N/A'C")));
        packTemp[i]->setFixedWidth(this->width()/columns-20);
        packTemp[i]->setAlignment(Qt::AlignCenter);
    }

    /*for(int i = 0; i < columns; ++i)
    {
        grid->setColumnMinimumWidth(i, SCR_WIDTH/4 / columns);
    }*/
}

void EntryTemp::setTemp(int position, QString text)
{

}
