#include <QList>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "reqqueueitem.h"

class ReqQueue: QObject{
    Q_OBJECT
    
    public:
        ReqQueue(QNetworkAccessManager*);
        void push(QString, QNetworkRequest);
    
    public slots:
        ReqQueueItem pop(void);
        void onFinishedRequest(QNetworkReply*);

    private:
        int _id;
        QNetworkAccessManager *_nam;
        QList<ReqQueueItem> _reqlist;
};
