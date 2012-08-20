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

#ifndef WIDGETS_INFO_DOCKINFORMATIONMODEL_H
#define WIDGETS_INFO_DOCKINFORMATIONMODEL_H

/**
 * @file dockinformationmodel.h
 * @short Definition of Widgets::Info::DockInformationModel
 */

#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>

#include "providermanager.h"
#include "mixedproviderbase.h"

namespace Widgets
{

namespace Info
{

class DockInformationModelPrivate;

/**
 * @short Model for dock information
 *
 * This class is used to display information about
 * available docks. It uses information that
 * Widgets::Docks::MixedProviderBase provides.
 *
 * Provided informations are
 * - file, that is the filename.
 * - disambiguation, that is the disambiguation paramters.
 * - name, that is the name of the dock.
 * - description, that is a description of the dock.
 *
 * In order to get the informations, you should set
 * the providerManager() property.
 */
class DockInformationModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Provider manager
     */
    Q_PROPERTY(Widgets::ProviderManager * providerManager READ providerManager
               WRITE setProviderManager NOTIFY providerManagerChanged)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum DockInformationModelRole
    {
        /**
         * @short File role
         */
        FileRole,
        /**
         * @short Disambiguation role
         */
        DisambiguationRole,
        /**
         * @short Name role
         */
        NameRole,
        /**
         * @short Description role
         */
        DescriptionRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit DockInformationModel(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DockInformationModel();
    /**
     * @brief Provider manager
     * @return provider manager.
     */
    ProviderManager * providerManager() const;
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return the number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Count
     * @return count.
     */
    int count() const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /**
     * @brief Clear the model
     */
    void clear();
Q_SIGNALS:
    /**
     * @brief Provider manager changed
     */
    void providerManagerChanged();
    /**
     * @short Count changed
     */
    void countChanged();
public Q_SLOTS:
    /**
     * @brief Set the provider manager
     * @param providerManager provider manager.
     */
    void setProviderManager(ProviderManager *providerManager);
    /**
     * @brief Update the model
     */
    void update();
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<DockInformationModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DockInformationModel)
    Q_PRIVATE_SLOT(d_func(), void slotProviderStatusChanged())
};

}

}

#endif // WIDGETS_INFO_DOCKINFORMATIONMODEL_H
