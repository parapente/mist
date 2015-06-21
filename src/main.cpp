#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Over the clouds");
    app.setApplicationName("Mist");

    qDebug() << "Hello World!";

    MainWindow mainWin;

    app.setActiveWindow(&mainWin);
    mainWin.show();
    app.exec();
    return 0;
}

