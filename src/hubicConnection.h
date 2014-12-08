#ifndef HUBICCONNECTION_H
#define HUBICCONNECTION_H

#include <QUrl>
#include <o2.h>
#include <o2requestor.h>

class HubicConnection {
    Q_OBJECT
    
    public:
        HubicConnection();
        ~HubicConnection();
        
    public slots:
        void initConnection(void);
        void onOpenBrowser(QUrl url);
        
    private:
        QString clientId;
        QString clientSecret;
        QString scope;
        QString requestUrl;
        int localPort;
        
        O2 *hubicCon;
        O2Requestor *hubicReq;

};

#endif // HUBICCONNECTION_H
