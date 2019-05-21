#include <QApplication>

#include "mainwindow.h"
#include "pushbuttons.h"

int SCR_WIDTH = 800;
int SCR_HEIGHT = 480;

Notice *Notice::noticeObject = nullptr;
EntryErrors *EntryErrors::errorsObject = nullptr;
PushButtons *isrObject = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
