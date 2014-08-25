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
    hubicCon = new O2(this);
    hubicCon->setClientId("api_hubic_NhdELNrW2JTB4cUewEoeKuDJBrA4uGeI");
    hubicCon->setClientSecret("Fk0qQUfla9COjLumln0tIDQ6l5NaheGhX5RJiLBCIwKxMxaHyxWyQEXHeJx91G7N");
    hubicCon->setScope("usage.r,account.r,getAllLinks.r,credentials.r,activate.w,links.drw");
    hubicCon->setRequestUrl("https://api.hubic.com/oauth/auth");
    hubicCon->setLocalPort(50050);
    connect(hubicCon, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(hubicCon, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(hubicCon, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(hubicCon, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(hubicCon, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));
    connect(ui->actionHubiC, SIGNAL(triggered(bool)), this, SLOT(onHubicPressed()));
}

MainWindow::~MainWindow()
{
    hubicCon->unlink();
    delete hubicCon;
    delete ui;
}

void MainWindow::onOpenBrowser(QUrl url)
{
    mistWebDialog webDialog;
    //webDialog.openUrl(QUrl("https://api.hubic.com/oauth/auth/"));
    webDialog.openUrl(url);
    webDialog.exec();
}

void MainWindow::onHubicPressed()
{
    hubicCon->link();
}
