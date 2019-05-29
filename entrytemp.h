#ifndef ENTRYTEMP_H
#define ENTRYTEMP_H

#include "entry.h"

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

#define PACK_COUNT 40
/* Entry that shows available battery cell temperatures
 * with preconfigured count.
 */

class MainWindow;


class EntryTemp : public Entry
{
public:
    EntryTemp(MainWindow *parent);
    void setTemp(int position, QString text);
private:
    QLabel *packTemp[PACK_COUNT];
    QGridLayout *grid = entryLayout;
};

#endif // ENTRYTEMP_H
