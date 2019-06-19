#include "entryerrors.h"
#include <QTime>

// Near carbon copy of EntrySerialLog

EntryErrors::EntryErrors(MainWindow *parent)
{
    EntryErrors::errorsObject = this;

    entryLayout->addWidget(col0,0,0);
    entryLayout->addWidget(col1,0,1);
    entryLayout->setMargin(15);
    entryLayout->setSpacing(5);

    QPalette p = col0->palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::black);
    col0->setPalette(p);
    col0->setBackgroundVisible(false);
    col0->setStyleSheet(
                "QPlainTextEdit{border-style: none;\
                                color: white;}");
    col1->setPalette(p);
    col1->setBackgroundVisible(false);
    col1->setStyleSheet(col0->styleSheet());

    int lineCount = 32;
    col0->setMaximumBlockCount(lineCount);
    col1->setMaximumBlockCount(lineCount);

    col0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    col1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}


void EntryErrors::addLine(QString line)
{
    EntryErrors::errorsObject->m_addLine(line);
}

void EntryErrors::m_addLine(QString line)
{
    QTextCursor cursor0 = col0->textCursor();
    QTextCursor cursor1 = col1->textCursor();
    cursor0.setPosition(QTextCursor::Start-1);

    QTime currentTime = QTime::currentTime();
    cursor0.insertText(currentTime.toString()+" - "+line+"\n");

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
