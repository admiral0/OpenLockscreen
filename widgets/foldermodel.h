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
 * @short Definition of Widgets::FolderModel
 *
 * This file contains the definition of the
 * Widgets::FolderModel class.
 */

#ifndef WIDGETS_FOLDERMODEL_H
#define WIDGETS_FOLDERMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QMetaType>

namespace Widgets
{

class ApplicationInformations;


/**
 * @short Model for applications folder
 *
 * This class is the model that manages the content
 * of an applications folder.
 *
 * Each item of this model is either an ApplicationInformations
 * that is used to provide all informations about
 * an application or a FolderModel, that is used to
 * provide the subfolder model.
 */
class FolderModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Number of rows in the model
     *
     * This property is mainly used in QML context
     * and is used by the views to track the number
     * of elements in the model.
     *
     * This property is nearly equivalent to
     * rowCount().
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
     *
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
     * This method is the reimplementation of
     * QAbstractListModel::rowCount(). It
     * simply returns the number of rows in this model.
     *
     * @param parent parent model index.
     * @return the number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Number of rows in this model
     *
     * This method is used to retrieve the number
     * of rows in this model.
     *
     * @return number of rows in this model.
     */
    int count() const;
    /**
     * @short Reimplementation of data
     *
     * This method is the reimplementation of
     * QAbstractListModel::data(). It is used
     * by views to retrieve the different
     * roles of the model, based on the row.
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
     *
     * Notify that the row count
     * has changed.
     *
     * @param count value of the new row count.
     */
    void countChanged(int count);
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
private:
    class FolderModelPrivate;
    /**
     * @short D-pointer
     */
    FolderModelPrivate * const d;
};

}

Q_DECLARE_METATYPE(Widgets::FolderModel *)

#endif // WIDGETS_FOLDERMODEL_H
