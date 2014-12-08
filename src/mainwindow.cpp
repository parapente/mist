#include "mainwindow.h"
#include "mistwebdialog.h"
#include "hubicConnection.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QWebView>
#include <QSslError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hubicCon = new hubicConnection();
    connect(ui->actionHubiC, SIGNAL(triggered(bool)), hubicCon, SLOT(initConnection()));
}

MainWindow::~MainWindow()
{
    hubicCon->unlink();
    delete hubicCon;
    delete ui;
}