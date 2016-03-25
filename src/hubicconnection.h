#ifndef HUBICCONNECTION_H
#define HUBICCONNECTION_H

#include <QUrl>
#include <QMap>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <o2.h>
#include <o2requestor.h>
#include <o2hubic.h>
#include "mistwebdialog.h"
#include "reqqueue.h"

class HubicConnection : public O2Hubic {
    Q_OBJECT
    
    public:
        HubicConnection();
        ~HubicConnection();

    signals:
        void linkSucceeded(void);

    public slots:
        void initConnection(void);
        void onOpenBrowser(QUrl url);
        void onCloseBrowser(void);
        void onLinkingFailed(void);
        void onLinkedChanged(void);
        void onLinkingSucceeded(void);
        
    private:
        QString base_url;
        QString clientId;
        QString clientSecret;
        int localPort;
        enum {O2_HUBIC_ACCOUNT, O2_HUBIC_ACCOUNT_CREDENTIALS, O2_HUBIC_ACCOUNT_GETALLLINKS, O2_HUBIC_ACCOUNT_GET_LINKS, O2_HUBIC_ACCOUNT_POST_LINKS, O2_HUBIC_ACCOUNT_GET_LINKS_URI, O2_HUBIC_ACCOUNT_DEL_LINKS_URI, O2_HUBIC_ACCOUNT_USAGE};
        QHash<int, int> reqhash;

        mistWebDialog *webDialog;
        QNetworkReply *reply;
        QNetworkAccessManager *manager;
        O2Requestor *requestor;
        ReqQueue *queue;

        quint64 usedSpace;
        quint64 availableSpace;
        QString osEndpoint, osToken, osTokenExpiresOn;
        QString email, firstName, lastName, activated, creationDate, language, status, offer;

    private:
        QNetworkRequest nrprep(QUrl, QString);
        QNetworkRequest xnrprep(QUrl, QString);


private slots:
    void readData(QNetworkReply *reply);
};

#endif // HUBICCONNECTION_H
