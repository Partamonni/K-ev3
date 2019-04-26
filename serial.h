#ifndef SERIAL_H
#define SERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QWidget>
#include <QString>
#include <QTimer>

class QLabel;
class MainWindow;

class Serial : public QSerialPort
{
    Q_OBJECT
public:
    Serial(MainWindow *parent);

signals:
    void motorShut(bool state);

public slots:
    bool openSerialPort();
    void closeSerialPort();
    void readSerial();
    void writeSerial(const QByteArray &outData);

private slots:
    void stopBreak();
    void handleError(QSerialPort::SerialPortError error);

private:
    void display(const QString &displayData);

    QString *inData = new QString;
    MainWindow *m_parent;
    QTimer *breakTimer = new QTimer;

    int dataEntry = 0;
    bool overT = false;
    bool overV = false;
    bool overC = false;
    bool underV = false;
};

#endif // SERIAL_H
