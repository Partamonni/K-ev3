#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>

class MainWindow;

class Entry : public QLabel
{
    Q_OBJECT
public:
    Entry(MainWindow *parent = nullptr);
    bool isClosing();

public slots:
    void toggleEntry();

protected:
    QGridLayout *entryLayout = new QGridLayout;
    QGridLayout *bgLayout = new QGridLayout;
    QPixmap *entryBg = new QPixmap;
    QPixmap *entryRender;
    QWidget *entryFrame = new QWidget;

private:
    QPropertyAnimation *motEffEntry = new QPropertyAnimation(this, "pos");

    int entWidth;
    bool entryOpen;
    MainWindow *m_parent;

private slots:
    void hideEntry();
};
#endif // ENTRY_H
