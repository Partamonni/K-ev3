#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTimer>

class MainWindow;

class Entry : public QLabel
{
    Q_OBJECT
public:
    Entry(MainWindow *parent = nullptr);
    bool isClosing();
    bool hidesPrevious();

signals:

public slots:
    virtual void toggleEntry();

protected:
    QGridLayout *entryLayout = new QGridLayout;
    QGridLayout *bgLayout = new QGridLayout;
    QPixmap *entryBg = new QPixmap;
    QPixmap *entryRender = nullptr;
    QWidget *entryFrame = new QWidget;
    QTimer *timer = new QTimer;
    QPropertyAnimation *motEffEntry = new QPropertyAnimation(this, "pos");
    MainWindow *m_parent = nullptr;

    bool hidePrevious = true;

private:
    int entWidth = 0;
    bool entryOpen = false;

private slots:
    void hideEntry();
};
#endif // ENTRY_H
