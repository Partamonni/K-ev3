#ifndef ENTRYSTATS_H
#define ENTRYSTATS_H

#include "entry.h"
#include <QPlainTextEdit>

class MainWindow;

class EntryStats : public Entry
{
public:
    EntryStats(MainWindow *parent);

    void addLine(QString line);

private:
    QPlainTextEdit *col0 = new QPlainTextEdit;
    QPlainTextEdit *col1 = new QPlainTextEdit;
};

#endif // ENTRYSTATS_H
