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
    connect(ui->actionHubiC, SIGNAL(triggered(bool)), hubicCon, SLOT(initConnection()));
    connect(ui->actionConnectHubic, SIGNAL(triggered(bool)), hubicCon, SLOT(initConnection()));
    connect(ui->actionDisconnectHubic, SIGNAL(triggered(bool)), hubicCon, SLOT(unlink()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(hubicCon, SIGNAL(linkSucceeded()), this, SLOT(hubicLinkToggle()));

    QStringList headers;
    headers << "Name";

    model = new mistRemoteFSModel(headers);
    ui->treeView->setModel(model);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeViewContextMenu(QPoint)));

    model->insertRows(0,1,QModelIndex());
    model->setData(model->index(0,0), QString("hubiC"), Qt::DisplayRole);
    model->setData(model->index(0,0), QIcon::fromTheme("dialog-error"), Qt::DecorationRole);
    model->setData(model->index(0,0), QBrush(palette().color(QPalette::Disabled, QPalette::WindowText)), Qt::ForegroundRole);
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
        model->setData(model->index(0,0), QIcon::fromTheme("network-server"), Qt::DecorationRole);
        model->setData(model->index(0,0), QBrush(palette().color(QPalette::Active, QPalette::WindowText)), Qt::ForegroundRole);
        qDebug() << "Data set... Now what?";
    }
    else {
        model->setData(model->index(0,0), QIcon::fromTheme("dialog-error"), Qt::DecorationRole);
        model->setData(model->index(0,0), QBrush(palette().color(QPalette::Disabled, QPalette::WindowText)), Qt::ForegroundRole);
        qDebug() << "Not linked??? Why?";
    }
}

void MainWindow::treeViewContextMenu(const QPoint &pos)
{
    qDebug() << "Context menu!";

    QModelIndex index;

    QMenu contextMenu(this);
    index = ui->treeView->indexAt(pos);
    if (index.isValid()) {
        if (!index.parent().isValid() && index.data().toString() == "hubiC") {
            if (!hubicCon->linked()) {
                contextMenu.addAction(ui->actionConnectHubic);
            }
            else {
                contextMenu.addAction(ui->actionDisconnectHubic);
            }
        }
        contextMenu.exec(ui->treeView->viewport()->mapToGlobal(pos));
    }
}
