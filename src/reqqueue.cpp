#include "reqqueue.h"

ReqQueue::ReqQueue(QNetworkAccessManager *nam)
{
    this->_nam = nam;
    this->_id = 1;
    connect(_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinishedRequest(QNetworkReply*)));
}

void ReqQueue::push(QString command, QNetworkRequest newreq)
{
    ReqQueueItem item;
    item.setCommand(command);
    item.setRequest(newreq);
    item.setId(this->_id++);
    _reqlist.append(item);
}

ReqQueueItem ReqQueue::pop()
{
    return _reqlist.takeFirst();
}

void ReqQueue::onFinishedRequest(QNetworkReply *req)
{
    // Remove this request from the list
    for (int i=0; i<_reqlist.count(); i++) {
        if (_reqlist.at(i).request() == req->request())
            _reqlist.removeAt(i);
    }

    // Start the next request
    ReqQueueItem nextItem = _reqlist.first();
    if (nextItem.command() == "get") {
        _nam->get(nextItem.request());
    }
    else if (nextItem.command() == "post") {

    }
}
