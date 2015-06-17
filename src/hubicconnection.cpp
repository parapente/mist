#include "hubicconnection.h"
#include <QDebug>
#include <QSettings>

HubicConnection::HubicConnection()
{
    hubicCon = new O2Hubic(this);
    webDialog = new mistWebDialog();

    // Set some default values
    scope = "usage.r,account.r,getAllLinks.r,credentials.r,activate.w,links.drw";
    requestUrl = "https://api.hubic.com/oauth/auth";
    
    // Connections to O2
    connect(hubicCon, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(hubicCon, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(hubicCon, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(hubicCon, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(hubicCon, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));

}

HubicConnection::~HubicConnection()
{
    if (hubicCon->linked())
        hubicCon->unlink();
    delete hubicCon;
}

void HubicConnection::initConnection(void)
{
    QSettings settings;

    clientId = settings.value("hubic/clientid").toString();
    clientSecret = settings.value("hubic/clientsecret").toString();
    if (clientId.isNull() || clientSecret.isNull()) { // Fix: Show id/secret dialog
        qDebug() << "No id/secret";
    }
    else {
        qDebug() << "Id/secret OK";
        hubicCon->setClientId(clientId);
        hubicCon->setClientSecret(clientSecret);
    }
    hubicCon->setScope(scope);
    hubicCon->setRequestUrl(requestUrl);
    hubicCon->setLocalPort(50050); // Fix: local port should be configurable
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
}
