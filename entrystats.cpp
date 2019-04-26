#include "entrystats.h"

EntryStats::EntryStats(MainWindow *parent)
{
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

    col0->setMaximumBlockCount(20);
    col1->setMaximumBlockCount(20);
    col0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    col1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

void EntryStats::addLine(QString line)
{
    QTextCursor cursor0 = col0->textCursor();
    QTextCursor cursor1 = col1->textCursor();
    cursor0.setPosition(QTextCursor::Start-1);

    cursor0.insertText(line+"\n");

    if(col0->blockCount() == col0->maximumBlockCount())
    {
        cursor0.movePosition(QTextCursor::End);
        cursor0.select(QTextCursor::LineUnderCursor);
        cursor1.setPosition(QTextCursor::Start-1);
        col1->insertPlainText(cursor0.selectedText());
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
