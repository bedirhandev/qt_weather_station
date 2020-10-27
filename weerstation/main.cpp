#include "mainwindow.h"
//#include <vld.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    // init app and main window
    QApplication a(argc, argv);
    MainWindow w;
    // show the window
    w.show();
    return a.exec();
}
