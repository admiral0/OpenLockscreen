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

#ifndef WIDGETS_EXTRA_WIDGETINFORMATIONMODEL_H
#define WIDGETS_EXTRA_WIDGETINFORMATIONMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>

#include "providermanager.h"
#include "widgetproviderbase.h"

namespace Widgets
{

namespace Extra
{

class WidgetInformationModelPrivate;
class WidgetInformationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Widgets::ProviderManager * providerManager READ providerManager
               WRITE setProviderManager NOTIFY providerManagerChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum WidgetInformationModelRole
    {
        FileRole,
        DisambiguationRole,
        NameRole,
        DescriptionRole
    };
    explicit WidgetInformationModel(QObject *parent = 0);
    virtual ~WidgetInformationModel();
    ProviderManager * providerManager() const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int count() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void clear();
Q_SIGNALS:
    void providerManagerChanged();
    void countChanged(int count);
public Q_SLOTS:
    void setProviderManager(Widgets::ProviderManager *providerManager);
    void update();
protected:
    const QScopedPointer<WidgetInformationModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(WidgetInformationModel)
    Q_PRIVATE_SLOT(d_func(), void slotProviderStatusChanged())
};

}

}

#endif // WIDGETS_EXTRA_WIDGETINFORMATIONMODEL_H
