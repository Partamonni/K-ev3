#ifndef NOTICE_H
#define NOTICE_H

/* Globally accessible and animated splash notification.
 * Needs a declaration of Notice::*noticeObject in main.cpp, which holds
 * the pointer to latest constructed class.
 */

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QVector>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class MainWindow;

class Notice : public QLabel
{
    Q_OBJECT
public:
    explicit Notice(MainWindow *parent = nullptr);

public slots:
    static void showText(QString);

private:
    MainWindow *m_parent = nullptr;
    QGridLayout *layout = new QGridLayout;
    QLabel *text = new QLabel();
    QPixmap *bgImg = new QPixmap(":/entrybg");
    QTimer *hideTimer = new QTimer;
    QFont *noticeFont = new QFont;
    static Notice *noticeObject;

    void initFont();

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacity, "opacity");

private slots:
    void toVisible();
};

#endif // NOTICE_H
