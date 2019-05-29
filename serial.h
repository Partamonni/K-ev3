#ifndef SERIAL_H
#define SERIAL_H

/* Serial class to handle serial communication
 * and to send received data to their destination widgets.
 */

/* Communications syntax
 * e = end of data (e~)
 * ? = host presence / continue operation query (?h)
 * ! = critical condition occurred (over[!C]urrent, over[!V]oltage, under[!v]oltage or high [!T]emperature)
 * u = power is on (up)
 * s = power is shut (sh)
 * : = data point (Battery [c]urrent, battery [v]voltage, # battery unit cell number and its temperature)
 */

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
    MainWindow *m_parent = nullptr;
    QTimer *breakTimer = new QTimer;

    int dataEntry = 0;
    bool overT = false;
    bool overV = false;
    bool overC = false;
    bool underV = false;
};

#endif // SERIAL_H
