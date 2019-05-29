#ifndef ENTRYSTATUS_H
#define ENTRYSTATUS_H

/* Text entry that could hold information about
 * battery capacity, capacity remaining, approximate range, battery health etc.
 */

#include "entry.h"
#include <QPlainTextEdit>

class MainWindow;

class EntryStatus : public Entry
{
public:
    EntryStatus(MainWindow *parent);

    void addLine(QString line);

private:
    QPlainTextEdit *col0 = new QPlainTextEdit;
    QPlainTextEdit *col1 = new QPlainTextEdit;
};

#endif // ENTRYSTATUS_H
