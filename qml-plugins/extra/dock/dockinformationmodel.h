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

#ifndef WIDGETS_EXTRA_DOCKINFORMATIONMODEL_H
#define WIDGETS_EXTRA_DOCKINFORMATIONMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>

#include "providermanager.h"
#include "mixedproviderbase.h"

namespace Widgets
{

namespace Extra
{

class DockInformationModelPrivate;
class DockInformationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Widgets::ProviderManager * providerManager READ providerManager
               WRITE setProviderManager NOTIFY providerManagerChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum DockInformationModelRole
    {
        FileRole,
        DisambiguationRole,
        NameRole,
        DescriptionRole
    };
    explicit DockInformationModel(QObject *parent = 0);
    virtual ~DockInformationModel();
    ProviderManager * providerManager() const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int count() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void clear();
Q_SIGNALS:
    void providerManagerChanged();
    void countChanged(int count);
public Q_SLOTS:
    void setProviderManager(ProviderManager *providerManager);
    void update();
protected:
    const QScopedPointer<DockInformationModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DockInformationModel)
    Q_PRIVATE_SLOT(d_func(), void slotProviderStatusChanged())
};

}

}

#endif // WIDGETS_EXTRA_DOCKINFORMATIONMODEL_H
