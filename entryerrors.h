#ifndef ENTRYERRORS_H
#define ENTRYERRORS_H

#include "entry.h"
#include <QPlainTextEdit>

/* Text entry to show error messages from the program.
 * OS error messages could maybe be relevant to add here in the future.
 */

class MainWindow;

class EntryErrors : public Entry
{
public:
    EntryErrors(MainWindow *parent);

    static void addLine(QString line);

private:
    // Text is contained within two columns
    QPlainTextEdit *col0 = new QPlainTextEdit;
    QPlainTextEdit *col1 = new QPlainTextEdit;

    void m_addLine(QString);

    static EntryErrors *errorsObject;
};

#endif // ENTRYERRORS_H
