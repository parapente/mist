#ifndef HUBICCONNECTION_H
#define HUBICCONNECTION_H

#include "mistwebdialog.h"
#include <QUrl>
#include <o2.h>
#include <o2requestor.h>
#include <o2hubic.h>

class HubicConnection : public QObject {
    Q_OBJECT
    
    public:
        HubicConnection();
        ~HubicConnection();
        
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
        QString scope;
        QString requestUrl;
        int localPort;
        
        O2Hubic *hubicCon;
        mistWebDialog *webDialog;
        O2Requestor *hubicReq;

};

#endif // HUBICCONNECTION_H
