#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>

class MainWindow;

class Entry : public QWidget
{
    Q_OBJECT
public:
    Entry(MainWindow *parent = nullptr);

public slots:
    void toggleEntry();

private:
    QGridLayout *entryLayout = new QGridLayout;
    QPixmap *entryBg = new QPixmap;
    QLabel *canvas = new QLabel(this);
    QPropertyAnimation *motEffEntry = new QPropertyAnimation(this, "pos");

    int entWidth;
    bool entryOpen;
    MainWindow *m_parent;

private slots:
    void hideEntry();
};
#endif // ENTRY_H
