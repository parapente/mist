#include "mainwindow.h"
#include "mistwebdialog.h"
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
    hubicCon = new HubicConnection();
    QObject::connect(ui->actionHubiC, SIGNAL(triggered(bool)), hubicCon, SLOT(initConnection()));
    QObject::connect(hubicCon, SIGNAL(linkSucceeded()), this, SLOT(hubicLinkToggle()));

    QStringList headers;
    headers << "Name";

    model = new mistRemoteFSModel(headers);
    ui->treeView->setModel(model);
    ui->treeView->setHeaderHidden(true);
}

MainWindow::~MainWindow()
{
    delete hubicCon;
    delete ui;
}

void MainWindow::hubicLinkToggle(void)
{
    qDebug() << "Link toggled!";
    if (hubicCon->linked()) {
        model->insertRows(0,1,QModelIndex());
        model->setData(model->index(0,0),QString("HubiC"),Qt::DisplayRole);
        model->setData(model->index(0,0),QIcon::fromTheme("network-server"),Qt::DecorationRole);
        qDebug() << "Data set... Now what?";
    }
    else {
        qDebug() << "Not linked??? Why?";
    }
}
