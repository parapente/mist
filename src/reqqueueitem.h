#ifndef REQQUEUEITEM_H
#define REQQUEUEITEM_H

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>

class ReqQueueItem
{
public:
    ReqQueueItem();
    ReqQueueItem(const ReqQueueItem&);
    ReqQueueItem(int, QString, QNetworkRequest);
    ReqQueueItem(int, QString, QNetworkReply*);
    ReqQueueItem &operator=(const ReqQueueItem&);
    ~ReqQueueItem();
    void setId(int);
    void setCommand(QString);
    void setRequest(QNetworkRequest);
    void setReply(QNetworkReply*);
    void setData(QByteArray);
    void setData(QHttpMultiPart*);
    int id(void) const;
    QString command(void) const;
    QNetworkRequest request(void) const;
    QByteArray* byteArray(void) const;
    QHttpMultiPart* multipart(void) const;
    QNetworkReply* reply(void) const;

private:
    int _id;
    QString _command;
    QNetworkRequest _request;
    QNetworkReply *_reply;
    QByteArray *_bytearray;
    QHttpMultiPart *_multipart;
};

#endif // REQQUEUEITEM_H
