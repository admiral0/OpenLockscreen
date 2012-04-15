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

#ifndef WIDGETS_EXTRA_PACKAGEMODEL_H
#define WIDGETS_EXTRA_PACKAGEMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>

namespace Widgets
{

namespace Extra
{

class PackageModelPrivate;
class PackageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum PackageRole
    {

    };

    explicit PackageModel(QObject *parent = 0);
    virtual ~PackageModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int count() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
Q_SIGNALS:
    void countChanged(int count);
public Q_SLOTS:
protected:
    const QScopedPointer<PackageModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(PackageModel)
};

}

}

#endif // WIDGETS_EXTRA_PACKAGEMODEL_H
