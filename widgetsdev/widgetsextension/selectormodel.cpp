/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

/**
 * @file selectormodel.cpp
 * @short Implementation of Widgets::SelectorModel
 *
 * This file contains the implemetation of the
 * Widgets::SelectorModel class and the declaration and
 * implementation of Widgets::SelectorModel::SelectorModelPrivate
 * and Widgets::SelectorModelItem.
 */

#include "selectormodel.h"

namespace Widgets
{

/**
 * @internal
 * @short Structure used in the SelectorModel
 *
 * This structure is used to store
 * the components in SelectorModel.
 */
struct SelectorModelItem
{
    /**
     * @short Identifier
     */
    QVariant identifier;
    /**
     * @short Text
     */
    QString text;
    /**
     * @short Sub-text
     */
    QString subText;
    /**
     * @short Icon
     */
    QString icon;
    /**
     * @short Indicator icon
     */
    QString indicatorIcon;
};

/**
 * @internal
 * @short Private class for SelectorModel
 */
class SelectorModel::SelectorModelPrivate
{
public:
    /**
     * @short Destructor
     */
    ~SelectorModelPrivate();
    /**
     * @short A list of SelectorModelItem
     *
     * This list of SelectorModelItem is the
     * internal storage of the model.
     */
    QList<SelectorModelItem *> items;
};

SelectorModel::SelectorModelPrivate::~SelectorModelPrivate()
{
    // Delete allocated items
    while(!items.isEmpty()) {
        delete items.takeFirst();
    }
}

////// End of private class //////

SelectorModel::SelectorModel(QObject *parent) :
    QAbstractListModel(parent), d(new SelectorModelPrivate)
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(IdentifierRole, "identifier");
    roles.insert(TextRole, "text");
    roles.insert(SubTextRole, "subText");
    roles.insert(IconRole, "icon");
    roles.insert(IndicatorIconRole, "indicatorIcon");
    setRoleNames(roles);
}

SelectorModel::~SelectorModel()
{
    delete d;
}

int SelectorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->items.count();
}

int SelectorModel::count() const
{
    return rowCount();
}

QVariant SelectorModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 or index.row() >= rowCount())
    {
        return QVariant();
    }

    SelectorModelItem * item = d->items.at(index.row());

    switch(role) {
    case IdentifierRole:
        return item->identifier;
        break;
    case TextRole:
        return item->text;
        break;
    case SubTextRole:
        return item->subText;
        break;
    case IconRole:
        return item->icon;
        break;
    case IndicatorIconRole:
        return item->indicatorIcon;
        break;
    default:
        return QVariant();
        break;
    }
}

void SelectorModel::addEntry(const QVariant &identifier,
                             const QString &text, const QString &subText,
                             const QString &icon, const QString &indicatorIcon)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    SelectorModelItem * item = new SelectorModelItem;
    item->identifier = identifier;
    item->text = text;
    item->subText = subText;
    item->icon = icon;
    item->indicatorIcon = indicatorIcon;
    d->items.append(item);

    emit countChanged(rowCount());
    endInsertRows();
}

}
