#include <QApplication>
#include <QSettings>
#include "mainwindow.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Over the clouds");
    app.setApplicationName("Mist");

    QSettings settings;

    settings.setValue("testSetting", "OK");

    cout << "Hello World!" << endl;

    MainWindow mainWin;

    app.setActiveWindow(&mainWin);
    mainWin.show();
    app.exec();
    return 0;
}

