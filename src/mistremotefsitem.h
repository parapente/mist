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

#ifndef MISTREMOTEFSITEM_H
#define MISTREMOTEFSITEM_H
#include <QList>
#include <QVector>
#include <QVariant>
#include <QIcon>
#include <QBrush>
#include <QDebug>

class mistRemoteFSItem
{
public:
    mistRemoteFSItem(const QVector<QVariant> &data, mistRemoteFSItem *parent=0);
    ~mistRemoteFSItem();

    void appendChild(mistRemoteFSItem *child);

    mistRemoteFSItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int role) const;
    bool setData(int column, QVariant data, int role);
    int row() const;
    mistRemoteFSItem *parent();
    bool insertChildren(int position, int count, int columns);
    bool removeChildren(int position, int count);

private:
    QList<mistRemoteFSItem*> childItems;
    QVector<QVariant> itemData;
    QIcon itemIcon;
    QBrush itemBrush;
    mistRemoteFSItem *parentItem;
};

#endif // MISTREMOTEFSITEM_H
