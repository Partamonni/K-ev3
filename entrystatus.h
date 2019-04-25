#ifndef ENTRYSTATUS_H
#define ENTRYSTATUS_H

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
