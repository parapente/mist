#include "reqqueueitem.h"

ReqQueueItem::ReqQueueItem()
{
    _bytearray = NULL;
    _multipart = NULL;
    _reply = NULL;
    _receiver = NULL;
    _slot = NULL;
}

ReqQueueItem::ReqQueueItem(int id, QString command, QNetworkRequest request) : _id(id), _command(command), _request(request)
{
    _bytearray = NULL;
    _multipart = NULL;
    _reply = NULL;
    _receiver = NULL;
    _slot = NULL;
}

ReqQueueItem::ReqQueueItem(int id, QString command, QNetworkReply* reply) : _id(id), _command(command), _reply(reply)
{
    _bytearray = NULL;
    _multipart = NULL;
    _receiver = NULL;
    _slot = NULL;
}

ReqQueueItem::ReqQueueItem(const ReqQueueItem &other)
{
    _command = other.command();
    _id = other.id();
    _request = other.request();
    _bytearray = other.byteArray();
    _multipart = other.multipart();
    _reply = other.reply();
    _receiver = other.receiver();
    _slot = other.receiverSlot();
}

ReqQueueItem& ReqQueueItem::operator =(const ReqQueueItem& other)
{
    _command = other.command();
    _id = other.id();
    _request = other.request();
    _bytearray = other.byteArray();
    _multipart = other.multipart();
    _reply = other.reply();
    _receiver = other.receiver();
    _slot = other.receiverSlot();
}

ReqQueueItem::~ReqQueueItem()
{
    if (_bytearray)
        delete _bytearray;
    if (_multipart)
        delete _multipart;
}

QString ReqQueueItem::command() const
{
    return _command;
}

int ReqQueueItem::id() const
{
    return _id;
}

QNetworkRequest ReqQueueItem::request() const
{
    return _request;
}

void ReqQueueItem::setCommand(QString cmd)
{
    _command = cmd;
}

void ReqQueueItem::setId(int id)
{
    _id = id;
}

void ReqQueueItem::setRequest(QNetworkRequest req)
{
    _request = req;
}

void ReqQueueItem::setData(QByteArray data)
{
    _bytearray = new QByteArray(data);
}

void ReqQueueItem::setData(QHttpMultiPart *mpart)
{
    _multipart = mpart;
}

QByteArray* ReqQueueItem::byteArray() const
{
    return _bytearray;
}

QHttpMultiPart* ReqQueueItem::multipart() const
{
    return _multipart;
}

QNetworkReply* ReqQueueItem::reply() const
{
    return _reply;
}

void ReqQueueItem::setReply(QNetworkReply* reply)
{
    _reply = reply;
}

void ReqQueueItem::setReceiver(QObject *obj)
{
    _receiver = obj;
}

void ReqQueueItem::setReceiverSlot(const char *slot)
{
    _slot = slot;
}

QObject* ReqQueueItem::receiver() const
{
    return _receiver;
}

const char* ReqQueueItem::receiverSlot() const
{
    return _slot;
}
