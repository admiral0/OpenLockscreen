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

#ifndef WIDGETS_INFO_PACKAGEINFORMATIONMODEL_H
#define WIDGETS_INFO_PACKAGEINFORMATIONMODEL_H

/**
 * @file packageinformationmodel.h
 * @short Definition of Widgets::Info::PackageInformationModel
 */

#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>

#include "packagemanager.h"

namespace Widgets
{

namespace Info
{

class PackageInformationModelPrivate;

/**
 * @short Model for package information
 *
 * This class is used to display information about
 * available packages. It uses information that
 * Widgets::PackageManager::PackageManager provides.
 *
 * Provided informations are
 * - name, that is the name of the package.
 * - description, that is a description of the package.
 * - author, that is the author of the package.
 * - email, that is the email of the package.
 * - website, that is the website of the package.
 * - version, that is the version of the package.
 *
 * In order to get the informations, you should set
 * the packageManager() property.
 */
class PackageInformationModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Package manager
     */
    Q_PROPERTY(Widgets::Provider::PackageManager::PackageManager * packageManager
               READ packageManager WRITE setPackageManager NOTIFY packageManagerChanged)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum PackageManagerInformationModelRole
    {
        /**
         * @short Name role
         */
        NameRole,
        /**
         * @short Description role
         */
        DescriptionRole,
        /**
         * @short Author role
         */
        AuthorRole,
        /**
         * @short Email role
         */
        EmailRole,
        /**
         * @short Website role
         */
        WebsiteRole,
        /**
         * @short Version role
         */
        VersionRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit PackageInformationModel(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~PackageInformationModel();
    /**
     * @brief Package manager
     * @return package manager.
     */
    Provider::PackageManager::PackageManager * packageManager() const;
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
     * @brief Package manager changed
     */
    void packageManagerChanged();
    /**
     * @short Count changed
     */
    void countChanged();
public Q_SLOTS:
    /**
     * @brief Set the package manager
     * @param packageManager package manager.
     */
    void setPackageManager(Widgets::Provider::PackageManager::PackageManager *packageManager);
    /**
     * @brief Update the model
     */
    void update();
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<PackageInformationModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(PackageInformationModel)
};

}

}

#endif // WIDGETS_EXTRA_PACKAGEINFORMATIONMODEL_H
