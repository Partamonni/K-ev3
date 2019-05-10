#ifndef NOTICE_H
#define NOTICE_H

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

signals:

public slots:
    static void showText(QString);
    /*
    int addText(QString);
    void clear(int);
    void clearAll();*/

private:
    //QString m_content = "BOOT COMPLETE!";
    QVector<int> noticeId;
    MainWindow *m_parent;
    QGridLayout *layout = new QGridLayout;
    QLabel *text = new QLabel();
    QPixmap *bgImg = new QPixmap(":/entrybg");
    QTimer *hideTimer = new QTimer;
    QTimer *releaseTimer = new QTimer;
    QFont *noticeFont = new QFont;
    static Notice *noticeObject;

    void initFont();

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacity, "opacity");

    bool keepHidden = false;

private slots:
    void toVisible();
    void toHidden();
};

#endif // NOTICE_H
