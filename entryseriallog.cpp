#include "entryseriallog.h"
#include <QPlainTextEdit>
#include <QTextCursor>

EntrySerialLog::EntrySerialLog(MainWindow *parent)
{
    entryLayout->addWidget(col0,0,0);
    entryLayout->addWidget(col1,0,1);
    entryLayout->setMargin(15);
    entryLayout->setSpacing(5);

    // These hoops are needed to get the QPlainTextEdit widget background black
    QPalette p = col0->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::black);
    col0->setPalette(p);
    col0->setBackgroundVisible(false);
    col0->setStyleSheet(
                "QPlainTextEdit{border-style: none;\
                                color: white;}");
    // Same settings for second column
    col1->setPalette(p);
    col1->setBackgroundVisible(false);
    col1->setStyleSheet(col0->styleSheet());

    // Defines how many lines are shown at once
    int lineCount = 32;
    col0->setMaximumBlockCount(lineCount);
    col1->setMaximumBlockCount(lineCount);

    col0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    col1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

// This function handles inserting lines to column 0 and
// moving them from column 0 to 1 when column 0 fills up.

void EntrySerialLog::addLine(QString line)
{
    QTextCursor cursor0 = col0->textCursor();
    QTextCursor cursor1 = col1->textCursor();
    cursor0.setPosition(QTextCursor::Start-1);

    cursor0.insertText(line+"\n");

    if(col0->blockCount() >= col0->maximumBlockCount())
    {
        cursor0.movePosition(QTextCursor::End);
        cursor0.select(QTextCursor::LineUnderCursor);
        cursor1.setPosition(QTextCursor::Start-1);
        cursor1.insertText(cursor0.selectedText()+"\n");
        cursor0.removeSelectedText();
        cursor0.deletePreviousChar();

        if(col1->blockCount() >= col1->maximumBlockCount())
        {
            cursor1.movePosition(QTextCursor::End);
            cursor1.select(QTextCursor::LineUnderCursor);
            cursor1.removeSelectedText();
            cursor1.deletePreviousChar();
        }
    }
}
