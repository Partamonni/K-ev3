#ifndef ENTRYSERIALLOG_H
#define ENTRYSERIALLOG_H

#include "entry.h"
#include <QPlainTextEdit>

/* Text entry that shows in- and outgoing messages nad some basic info of serial devices state.
 */

class MainWindow;

class EntrySerialLog : public Entry
{
    Q_OBJECT
public:
    EntrySerialLog(MainWindow *parent = nullptr);

    void addLine(QString line);

private:
    QPlainTextEdit *col0 = new QPlainTextEdit;
    QPlainTextEdit *col1 = new QPlainTextEdit;
};

#endif // ENTRYSERIALLOG_H
