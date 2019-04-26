#ifndef ENTRYMOTOR_H
#define ENTRYMOTOR_H

#include "entry.h"
#include "serial.h"

class MainWindow;

class EntryMotor : public Entry
{
public:
    EntryMotor(MainWindow *parent);

    void toggleEntry();
    void setSerial(Serial *serialObject);

private:
    bool powerEnabled = false;
    Serial *serial = nullptr;
};

#endif // ENTRYMOTOR_H
