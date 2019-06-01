#ifndef ENTRYMOTOR_H
#define ENTRYMOTOR_H

#include "entry.h"
#include "serial.h"

/* Sends serial message to start/continue operation, as in powering the motor on, if possible.
 * Doesn't open visual entry and doesn't thus block other entries.
 * Needs to be provided a Serial class that has Serial::writeSerial() function.
 */

class MainWindow;

class EntryMotor : public Entry
{
    Q_OBJECT

public:
    EntryMotor(MainWindow *parent);

    void toggleEntry();
    void setSerial(Serial *serialObject);
    void success(bool isShut);

public slots:
    void alertFailure();

signals:

private:
    bool powerEnabled = false;
    int retries = 0;
    Serial *serial = nullptr;

friend Serial;
};

#endif // ENTRYMOTOR_H
