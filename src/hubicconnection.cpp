#include "hubicconnection.h"
#include <QDebug>
#include <QSettings>
#include <QUrlQuery>
#include "o2globals.h"

HubicConnection::HubicConnection()
{
    base_url = "https://api.hubic.com/1.0";
    webDialog = new mistWebDialog();

    // Connections to O2
    connect(this, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(this, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(this, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(this, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(this, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readData(QNetworkReply*)));
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

    if (linked()) {
        // On success get account info
        QUrl url(base_url + "/account");
        //query.addQueryItem("access_token", this->token().toUtf8());
        QNetworkRequest request(url);
        request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
        request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + token().toUtf8());

        manager->get(request);
        
        //Get OpenStack credentials
        url = QUrl(base_url + "/account/credentials");
        QNetworkRequest cred_request(url);
        cred_request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
        cred_request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + token().toUtf8());

        manager->get(cred_request);
    }
}

void HubicConnection::readData(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << reply->readAll();
    }
    else {
        qDebug() << "Error! Errno: " << reply->error();
        qDebug() << reply->errorString();
    }
}
