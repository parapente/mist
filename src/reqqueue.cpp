#include "reqqueue.h"

ReqQueue::ReqQueue(QNetworkAccessManager *nam)
{
    _nam = nam;
    _id = 1;
    _numconnections = 1;
    connect(_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinishedRequest(QNetworkReply*)));
}

void ReqQueue::push(QString command, QNetworkRequest newreq)
{
    ReqQueueItem item;
    item.setCommand(command);
    item.setRequest(newreq);
    item.setId(_id++);
    _reqlist.append(item);

    if (_numconnections)
        startNextReq();
}

ReqQueueItem ReqQueue::pop()
{
    return _reqlist.takeFirst();
}

void ReqQueue::onFinishedRequest(QNetworkReply *req)
{
    // Remove this request from the list
    QMutableListIterator<ReqQueueItem> i(_reqlist);
    while (i.hasNext()) {
        i.next();
        if (i.value().request().url() == req->request().url()) {
            i.remove();
            //qDebug() << "Removed item " << i;
            qDebug() << "Equal!";
        }
        else {
            qDebug() << "Not equal!";
            qDebug() << i.value().request().url();
            qDebug() << req->request().url();
        }
    }
    _numconnections++;
    qDebug() << "Num connections: " << _numconnections;

    if (_reqlist.size() != 0)
        startNextReq();
}

void ReqQueue::startNextReq(void)
{
    // Start the next request
    ReqQueueItem nextItem = _reqlist.first();
    if (nextItem.command() == "get") {
        nextItem.setReply(_nam->get(nextItem.request()));
    }
    else if (nextItem.command() == "post") {
        if (nextItem.multipart()) {
            _nam->post(nextItem.request(), nextItem.multipart());
        }
        else {
            _nam->post(nextItem.request(), *(nextItem.byteArray()));
        }
    }
    else {
        qDebug() << "Command " << nextItem.command() << " not supported!!!";
    }

    _numconnections--;
    qDebug() << "Num connections: " << _numconnections;
}
