#include "hubicConnection.h"

HubicConnection::HubicConnection()
{
    hubicCon = new O2(this);

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
    delete hubicCon;
}

void HubicConnection::initConnection(void)
{
    hubicCon->setClientId("api_hubic_NhdELNrW2JTB4cUewEoeKuDJBrA4uGeI"); // Fix: ClientID and ClientSecret should be read from configuration file
    hubicCon->setClientSecret("Fk0qQUfla9COjLumln0tIDQ6l5NaheGhX5RJiLBCIwKxMxaHyxWyQEXHeJx91G7N");
    hubicCon->setScope(scope);
    hubicCon->setRequestUrl(requestUrl);
    hubicCon->setLocalPort(50050); // Fix: local port should be configurable
}

void HubicConnection::onOpenBrowser(QUrl url)
{
    mistWebDialog webDialog;
    //webDialog.openUrl(QUrl("https://api.hubic.com/oauth/auth/"));
    webDialog.openUrl(url);
    webDialog.exec();
}
