#ifndef REQQUEUE_H
#define REQQUEUE_H

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
        int _numconnections;
        QNetworkAccessManager *_nam;
        QList<ReqQueueItem> _reqlist;

    private:
        void startNextReq(void);
};

#endif // REQQUEUE_H
