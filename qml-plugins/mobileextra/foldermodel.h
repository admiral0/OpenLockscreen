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
 * @file foldermodel.h
 * @short Definition of Widgets::MobileExtra::FolderModel
 */

#ifndef WIDGETS_MOBILEEXTRA_FOLDERMODEL_H
#define WIDGETS_MOBILEEXTRA_FOLDERMODEL_H

#include <QtCore/QAbstractListModel>

namespace Widgets
{

namespace MobileExtra
{

class ApplicationInformations;
class FolderModelPrivate;
/**
 * @short Model for applications folder
 *
 * This class is the model that manages the content
 * of an applications folder.
 *
 * Each item of this model is either an
 * Widgets::MobileExtra::ApplicationInformations
 * that is used to provide all informations about
 * an application or a
 * Widgets::MobileExtra::FolderModel, that is used to
 * provide the subfolder model.
 */
class FolderModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_ENUMS(Type)
public:
    /**
     * @short Entry type
     */
    enum Type {
        /**
         * @short The entry is an application
         */
        ApplicationType,
        /**
         * @short The entry is a folder
         */
        FolderType
    };
    /**
     * @short Model roles
     */
    enum FolderRole {
        /**
         * @short Index role
         */
        IndexRole = Qt::UserRole + 1,
        /**
         * @short Name role
         */
        NameRole,
        /**
         * @short Type role
         */
        TypeRole,
        /**
         * @short Properties role
         */
        PropertiesRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit FolderModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~FolderModel();
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Count
     * @return number of rows in this model.
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
     * @short Path to icon
     *
     * This method is used to retrieve directly
     * the path to an icon by providing the index
     * of the icon to retrieve.
     *
     * @param index index of the icon to retrieve.
     * @return path to the icon at the given index.
     */
    Q_INVOKABLE QString icon(int index) const;
Q_SIGNALS:
    /**
     * @short Count changed
     */
    void countChanged();
public Q_SLOTS:
    /**
     * @short Add application
     *
     * This method is used to add an application
     * to the model, provided the name of the
     * application and the informations related
     * to the application.
     *
     * @param name name of the application.
     * @param applicationInformations informations related to the application.
     */
    void addApplication(const QString &name, ApplicationInformations *applicationInformations);
    /**
     * @short Add subfolder
     *
     * This method is used to add a subfolder
     * to the model, provided the name of the
     * subfolder and the model that describes
     * it.
     *
     * @param name name of the subfolder.
     * @param subfolderModel model that describes the subfolder.
     */
    void addSubfolder(const QString &name, FolderModel *subfolderModel);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    FolderModel(FolderModelPrivate *dd, QObject *parent = 0);
    /**
     * @short D-pointer
     */
    QScopedPointer<FolderModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FolderModel)
};

}

}

Q_DECLARE_METATYPE(Widgets::MobileExtra::FolderModel *)

#endif // WIDGETS_MOBILEEXTRA_FOLDERMODEL_H
