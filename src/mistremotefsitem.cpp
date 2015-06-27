/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  Θεόφιλος Ιντζόγλου <int.teo@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "mistremotefsitem.h"

mistRemoteFSItem::mistRemoteFSItem(const QVector<QVariant> &data, mistRemoteFSItem *parent)
{
    parentItem = parent;
    itemData = data;
}

mistRemoteFSItem::~mistRemoteFSItem()
{
    qDeleteAll(childItems);
}

void mistRemoteFSItem::appendChild(mistRemoteFSItem *item)
{
    childItems.append(item);
}

mistRemoteFSItem *mistRemoteFSItem::child(int row)
{
    return childItems.value(row);
}

int mistRemoteFSItem::childCount() const
{
    return childItems.count();
}

int mistRemoteFSItem::columnCount() const
{
    return itemData.count();
}

QVariant mistRemoteFSItem::data(int column, int role) const
{
    if (role == Qt::DecorationRole) {
        return itemIcon;
    }

    if (role == Qt::ForegroundRole) {
        return itemBrush;
    }

    return itemData.value(column);
}

bool mistRemoteFSItem::setData ( int column, QVariant data, int role )
{
    if (column<0 || column>=itemData.size())
        return false;

    if (role == Qt::DecorationRole) {
        if (data.canConvert<QIcon>()) {
            itemIcon = data.value<QIcon>();
            return true;
        }
        else
            return false;
    }

    if (role == Qt::ForegroundRole) {
        if (data.canConvert<QBrush>()) {
            itemBrush = data.value<QBrush>();
            return true;
        }
        else
            return false;
    }

    itemData[column] = data;
    return true;
}

mistRemoteFSItem *mistRemoteFSItem::parent()
{
    return parentItem;
}

int mistRemoteFSItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<mistRemoteFSItem*>(this));
    return 0;
}

bool mistRemoteFSItem::insertChildren ( int position, int count, int columns )
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        mistRemoteFSItem *item = new mistRemoteFSItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool mistRemoteFSItem::removeChildren ( int position, int count )
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
