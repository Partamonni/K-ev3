#ifndef ENTRYERRORS_H
#define ENTRYERRORS_H

#include "entry.h"
#include <QPlainTextEdit>

class MainWindow;

class EntryErrors : public Entry
{
public:
    EntryErrors(MainWindow *parent);

    void addLine(QString line);

private:
    QPlainTextEdit *col0 = new QPlainTextEdit;
    QPlainTextEdit *col1 = new QPlainTextEdit;
};

#endif // ENTRYERRORS_H
