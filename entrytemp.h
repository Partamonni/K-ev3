#ifndef ENTRYTEMP_H
#define ENTRYTEMP_H

#include "entry.h"

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

class MainWindow;


class EntryTemp : public Entry
{
public:
    EntryTemp(MainWindow *parent);
    void setTemp(int position, QString text);
private:
    QLabel *packTemp[40];
    QGridLayout *grid = entryLayout;
};

#endif // ENTRYTEMP_H
