#ifndef ENTRYERRORS_H
#define ENTRYERRORS_H

#include "entry.h"
#include <QPlainTextEdit>

class MainWindow;

class EntryErrors : public Entry
{
public:
    EntryErrors(MainWindow *parent);

    static void addLine(QString line);

private:
    QPlainTextEdit *col0 = new QPlainTextEdit;
    QPlainTextEdit *col1 = new QPlainTextEdit;

    void m_addLine(QString);

    static EntryErrors *errorsObject;
};

#endif // ENTRYERRORS_H
