#include "entrytemp.h"
#include "mainwindow.h"

#include <QLabel>
#include <math.h>

EntryTemp::EntryTemp(MainWindow *parent)
{
    int initCount = PACK_COUNT;

    // Initialize all those temperature labels
    for (int i = 0; i < initCount; ++i)
    {
        packTemp[i] = new QLabel;
        packTemp[i]->setFont(this->font());
        packTemp[i]->setStyleSheet("QLabel {background-color: rgba(0,0,0,80); color: white;}");
    }

    grid->setContentsMargins(15,20,15,20);

    // Get row count with given column count
    int columns = 4;
    int rows;
    double a = initCount;
    double b = columns;
    double rowsTmp = a/b;
    rows = static_cast<int>(ceil(rowsTmp));

    // Insert all those labels in a grid
    int col = 0;
    for(int i = 0; i < initCount; ++i)
    {
        if (i % rows == 0 && i != 0)
            ++col;

        grid->addWidget(packTemp[i], i - (col * rows), col, Qt::AlignCenter);
        packTemp[i]->setText((QString("N/A'C")));
        packTemp[i]->setFixedWidth(this->width() / columns - 20);
        packTemp[i]->setAlignment(Qt::AlignCenter);
    }
}

void EntryTemp::setTemp(int position, QString text)
{
    packTemp[position]->setText(text);
}
