#include "mistremotefsmodel.h"
#include "mistremotefsitem.h"

mistRemoteFSModel::mistRemoteFSModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

mistRemoteFSModel::~mistRemoteFSModel()
{
    delete rootItem;
}


int mistRemoteFSModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<mistRemoteFSItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

bool mistRemoteFSModel::setData ( const QModelIndex& index, const QVariant& value, int role )
{
    if (!index.isValid())
        return false;

    mistRemoteFSItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

QVariant mistRemoteFSModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    mistRemoteFSItem *item = static_cast<mistRemoteFSItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags mistRemoteFSModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant mistRemoteFSModel::headerData ( int section, Qt::Orientation orientation,
        int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return rootItem->data ( section );

    return QVariant();
}

QModelIndex mistRemoteFSModel::index ( int row, int column, const QModelIndex &parent )
const
{
    if ( !hasIndex ( row, column, parent ) )
        return QModelIndex();

    mistRemoteFSItem *parentItem;

    if ( !parent.isValid() )
        parentItem = rootItem;
    else
        parentItem = static_cast<mistRemoteFSItem*> ( parent.internalPointer() );

    mistRemoteFSItem *childItem = parentItem->child ( row );
    if ( childItem )
        return createIndex ( row, column, childItem );
    else
        return QModelIndex();
}

QModelIndex mistRemoteFSModel::parent ( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return QModelIndex();

    mistRemoteFSItem *childItem = static_cast<mistRemoteFSItem*> ( index.internalPointer() );
    mistRemoteFSItem *parentItem = childItem->parent();

    if ( parentItem == rootItem )
        return QModelIndex();

    return createIndex ( parentItem->row(), 0, parentItem );
}

int mistRemoteFSModel::rowCount ( const QModelIndex &parent ) const
{
    mistRemoteFSItem *parentItem;
    if ( parent.column() > 0 )
        return 0;

    if ( !parent.isValid() )
        parentItem = rootItem;
    else
        parentItem = static_cast<mistRemoteFSItem*> ( parent.internalPointer() );

    return parentItem->childCount();
}

mistRemoteFSItem* mistRemoteFSModel::getItem ( const QModelIndex& index ) const
{
    if (index.isValid()) {
        mistRemoteFSItem *item = static_cast<mistRemoteFSItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

bool mistRemoteFSModel::setHeaderData ( int section, Qt::Orientation orientation, const QVariant& value, int role )
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

bool mistRemoteFSModel::insertRows ( int row, int count, const QModelIndex& parent )
{
    mistRemoteFSItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    success = parentItem->insertChildren(row, count, rootItem->columnCount());
    endInsertRows();

    return success;
}

bool mistRemoteFSModel::removeRows ( int row, int count, const QModelIndex& parent )
{
    mistRemoteFSItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, row, row + count - 1);
    success = parentItem->removeChildren(row, count);
    endRemoveRows();

    return success;
}
