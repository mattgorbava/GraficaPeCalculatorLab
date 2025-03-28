#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("windowsvista");
    mainwindow w;
    w.show();
    return a.exec();
}
