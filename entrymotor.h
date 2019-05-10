#ifndef ENTRYMOTOR_H
#define ENTRYMOTOR_H

#include "entry.h"
#include "serial.h"

class MainWindow;

class EntryMotor : public Entry
{
    Q_OBJECT

public:
    EntryMotor(MainWindow *parent);

    void toggleEntry();
    void setSerial(Serial *serialObject);
    void success();

public slots:
    void alertFailure();

signals:

private:
    bool powerEnabled = false;
    bool stateChangeSuccess = false;
    int retries = 0;
    Serial *serial = nullptr;
};

#endif // ENTRYMOTOR_H
