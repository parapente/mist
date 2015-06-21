#ifndef MISTREMOTEFSMODEL_H
#define MISTREMOTEFSMODEL_H

#include <QAbstractItemModel>
#include <QStringList>

class mistRemoteFSItem;

class mistRemoteFSModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit mistRemoteFSModel(const QStringList &headers, QObject *parent = 0);
    virtual ~mistRemoteFSModel();

    // Item data handling
    QModelIndex index(int row, int column, const QModelIndex& parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent=QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent=QModelIndex());

private:
    mistRemoteFSItem *rootItem;
    mistRemoteFSItem *getItem(const QModelIndex &index) const;

signals:

public slots:

};

#endif // MISTREMOTEFSMODEL_H
