#ifndef HUBICCONNECTION_H
#define HUBICCONNECTION_H

#include "mistwebdialog.h"
#include <QUrl>
#include <o2.h>
#include <o2requestor.h>
#include <o2hubic.h>

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
        QString clientId;
        QString clientSecret;
        int localPort;

        mistWebDialog *webDialog;
        QNetworkReply *reply;

private slots:
    void readAccountData(int id, QNetworkReply::NetworkError error, QByteArray data);
};

#endif // HUBICCONNECTION_H
