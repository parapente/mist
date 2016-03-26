#include <QDebug>
#include <QSettings>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "hubicconnection.h"
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
    queue = new ReqQueue(manager);
    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readData(QNetworkReply*)));
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
        queue->push("get", nrprep(base_url + "/account", token()), this, SLOT(account()));
        
        // Get OpenStack credentials
        queue->push("get", nrprep(base_url + "/account/credentials", token()), this, SLOT(accountCredentials()));

        // Get Usage
        queue->push("get", nrprep(base_url + "/account/usage", token()), this, SLOT(accountUsage()));
    }
}

QNetworkRequest HubicConnection::nrprep(QUrl url, QString token)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + token.toUtf8());
    return request;
}

QNetworkRequest HubicConnection::xnrprep(QUrl url, QString token)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
    request.setRawHeader(QByteArray("X-Auth-Token"), token.toUtf8());
    return request;
}

void HubicConnection::accountUsage(void)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject jobj;

        jobj = QJsonDocument::fromJson(reply->readAll()).object();
        availableSpace = jobj.value("quota").toVariant().toULongLong();
        usedSpace = jobj.value("used").toVariant().toULongLong();

        qDebug() << "Quota: " << availableSpace;
        qDebug() << "Used: " << usedSpace;
    }
    else {
        qDebug() << "Error! Errno: " << reply->error();
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

void HubicConnection::accountCredentials(void)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject jobj;

        jobj = QJsonDocument::fromJson(reply->readAll()).object();
        osEndpoint = jobj.value("endpoint").toString();
        osToken = jobj.value("token").toString();
        osTokenExpiresOn = jobj.value("expires").toString();

        qDebug() << "Endpoint: " << osEndpoint;
        qDebug() << "Token: " << osToken;
        qDebug() << "Expires: " << osTokenExpiresOn;

        qDebug() << "Let's test connection to OpenStack api...";
        queue->push("get", xnrprep(osEndpoint, osToken), this, SLOT(getContainers()));
    }
    else {
        qDebug() << "Error! Errno: " << reply->error();
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

void HubicConnection::account(void)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject jobj;

        jobj = QJsonDocument::fromJson(reply->readAll()).object();
        email = jobj.value("email").toString();
        firstName = jobj.value("firstname").toString();
        lastName = jobj.value("lastname").toString();
        activated = jobj.value("activated").toString();
        creationDate = jobj.value("creationDate").toString();
        language = jobj.value("language").toString();
        status = jobj.value("status").toString();
        offer = jobj.value("offer").toString();

        qDebug() << "Firstname: " << firstName;
        qDebug() << "Lastname: " << lastName;
        qDebug() << "Email: " << email;
        qDebug() << "Activated: " << activated;
        qDebug() << "Creation Date: " << creationDate;
        qDebug() << "Language: " << language;
        qDebug() << "Status: " << status;
        qDebug() << "Offer: " << offer;
    }
    else {
        qDebug() << "Error! Errno: " << reply->error();
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

void HubicConnection::getContainers(void)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    if (reply->error() == QNetworkReply::NoError) {
        QJsonArray jarr;
        QJsonObject jobj;

        qDebug() << reply->readAll();
        //jarr = QJsonDocument::fromJson(reply->readAll()).array();
        //jarr.size();
    }
    else {
        qDebug() << "Error! Errno: " << reply->error();
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}
