#include "notice.h"



Notice::Notice(MainWindow *parent)
{
    m_parent = parent;
    noticeObject = this;
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

    text->setFont(*noticeFont);
    text->setStyleSheet("*{color: white;}");

    layout->addWidget(text,1,0,1,1,Qt::AlignCenter);

    this->setPixmap(bgImg->scaled(this->size()));

    hideTimer->setSingleShot(true);

    connect(hideTimer, SIGNAL(timeout()), opacityAnim, SLOT(start()));
    connect(opacityAnim, SIGNAL(finished()), this, SLOT(hide()));
}

void Notice::initFont()
{
    noticeFont->setFamily("Square Sans Serif 7");
    noticeFont->setPixelSize(20);
    noticeFont->setCapitalization(QFont::AllUppercase);
    noticeFont->setLetterSpacing(QFont::PercentageSpacing, 110);
    noticeFont->setStretch(75);
}

void Notice::showText(QString text)
{
    Notice::noticeObject->text->setText(text);
    Notice::noticeObject->toVisible();
}

void Notice::toVisible()
{
    opacity->setOpacity(1);
    this->show();
    this->raise();
    hideTimer->start(2000);
}
