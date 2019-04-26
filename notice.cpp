#include "notice.h"


Notice *Notice::mainObject = nullptr;

Notice::Notice(MainWindow *parent)
{
    m_parent = parent;
    mainObject = this;
    initFont();

    this->setFixedSize(400,180);
    this->setGraphicsEffect(opacity);
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setRowStretch(1,1);
    this->setLayout(layout);

    opacity->setOpacity(1);
    opacityAnim->setStartValue(1);
    opacityAnim->setEndValue(0);
    opacityAnim->setDuration(500);

    text->setText(m_content);
    text->setFont(*noticeFont);
    text->setStyleSheet("*{color: white;}");

    layout->addWidget(text,1,0,1,1,Qt::AlignCenter);

    this->setPixmap(bgImg->scaled(this->size()));

    hideTimer->setSingleShot(true);
    releaseTimer->setSingleShot(true);

    connect(hideTimer, SIGNAL(timeout()), opacityAnim, SLOT(start()));
    connect(releaseTimer, SIGNAL(timeout()), this, SLOT(hide()));
    connect(opacityAnim, SIGNAL(finished()), this, SLOT(hide()));

    show();
}

void Notice::initFont()
{
    noticeFont->setFamily("Square Sans Serif 7");
    noticeFont->setPixelSize(20);
    noticeFont->setCapitalization(QFont::AllUppercase);
    noticeFont->setLetterSpacing(QFont::PercentageSpacing, 110);
    noticeFont->setStretch(75);
}

int Notice::addText(QString addText)
{
    int i = -1;
    int freeId = -1; // -1 == non-free id

    while(freeId < 0)
    {
        ++i;
        freeId = i; // Put id up for test
        for(int j = 0; j >= noticeId.size();)
        {
            if(i == noticeId.at(j)) // If id exists, mark it non-free
            {
                freeId = -1;
                break; // Don't continue unnecessarily
            }
        }
    }

    noticeId.push_front(freeId);
    m_content.prepend("\n");
    m_content.prepend(addText);
    text->setText(m_content);
    this->show();
    return freeId;
}

void Notice::showText(QString setText)
{
    Notice::mainObject->setText(setText);
    Notice::mainObject->show();
}

void Notice::clear(int deleteId)
{
    bool clear = false;

    int line = -1;
    for(int i = 0; i < noticeId.size(); ++i)
    {
        if(noticeId.at(i) == deleteId)
        { // Go through id:s and return order index of one when match found
            line = i;
            break; // Don't go over unnecessary indexes
        }
    }

    if(line > -1)
    {
        int i = 0;
        int begin = 0;
        int end = 0;
        while(!clear)
        {
            begin = end+1; // Move previous index to be starting index
            end = m_content.indexOf("\n", begin);
            if(i == line)
            {
                m_content.remove(begin, (end - begin)+1);
                noticeId.remove(line);
                clear = true;
            }
            else
                ++i;
        }
    }
    else{}
        //error
}

void Notice::clearAll()
{
    m_content.clear();
    noticeId.clear();
}

void Notice::toVisible()
{
    if(!keepHidden)
    {
        opacity->setOpacity(1);
        this->show();
        this->raise();
        hideTimer->start(2000);
        keepHidden = true;
    }
}

void Notice::toHidden()
{

    if(keepHidden)
    {
        if(noticeId.isEmpty())
        {
            m_content.clear();
        }
        this->hide();
        releaseTimer->start(4000);
    }
    else
        keepHidden = false;
}
