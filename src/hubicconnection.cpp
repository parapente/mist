#include "hubicconnection.h"
#include <QDebug>
#include <QSettings>
#include "o2globals.h"

HubicConnection::HubicConnection()
{
    webDialog = new mistWebDialog();

    // Connections to O2
    connect(this, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(this, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(this, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(this, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(this, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));

}

HubicConnection::~HubicConnection()
{
    if (linked())
        unlink();
}

void HubicConnection::initConnection(void)
{
    QSettings settings;

    clientId = settings.value("hubic/clientid").toString();
    clientSecret = settings.value("hubic/clientsecret").toString();
    localPort = settings.value("hubic/localport").toInt();

    if (clientId.isNull() || clientSecret.isNull()) { // Fix: Show id/secret dialog
        qDebug() << "No id/secret";
    }
    else {
        qDebug() << "Id/secret OK";
        setClientId(clientId);
        setClientSecret(clientSecret);
    }
    setLocalPort(localPort);
    link();
}

void HubicConnection::onOpenBrowser(QUrl url)
{
    webDialog->openUrl(url);
    webDialog->exec();
}

void HubicConnection::onCloseBrowser(void)
{
    webDialog->close();
}

void HubicConnection::onLinkingFailed(void)
{
    qDebug() << "Link has failed!";
}

void HubicConnection::onLinkedChanged(void)
{
    qDebug() << "Link has changed?";
}

void HubicConnection::onLinkingSucceeded(void)
{
    qDebug() << "Success!!";
    emit linkSucceeded();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    O2Requestor *requestor = new O2Requestor(manager, this);

    QUrl url = QUrl("https://api.hubic.com/1.0/account");

    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + token().toUtf8());

    connect(requestor, SIGNAL(finished(int,QNetworkReply::NetworkError,QByteArray)), this, SLOT(readAccountData(int,QNetworkReply::NetworkError,QByteArray)));
    requestor->get(request);
}

void HubicConnection::readAccountData(int id, QNetworkReply::NetworkError error, QByteArray data)
{
    if (error == QNetworkReply::NoError) {
        qDebug() << data;
    }
    else {
        qDebug() << "Error! Errno: " << error;
    }
}
