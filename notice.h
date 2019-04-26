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

    QGridLayout *layout = new QGridLayout;
    QLabel *text = new QLabel();

signals:

public slots:
    int addText(QString);
    static void showText(QString);
    void clear(int);
    void clearAll();
    void toVisible();
    void toHidden();

private:
    QString m_content = "BOOT COMPLETE!";
    QVector<int> noticeId;
    MainWindow *m_parent;
    QPixmap *bgImg = new QPixmap(":/entrybg");
    QTimer *hideTimer = new QTimer;
    QTimer *releaseTimer = new QTimer;
    QFont *noticeFont = new QFont;
    static Notice *mainObject;

    void initFont();

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *opacityAnim = new QPropertyAnimation(opacity, "opacity");

    bool keepHidden = false;
};

#endif // NOTICE_H
