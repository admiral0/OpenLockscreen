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
 * @file displayeddocksmodel.h
 * @short Definition of Widgets::DisplayedDocksModel
 *
 * This file contains the definition of the
 * Widgets::DisplayedDocksModel class.
 */

#ifndef WIDGETS_DISPLAYEDDOCKSMODEL_H
#define WIDGETS_DISPLAYEDDOCKSMODEL_H

#include <QAbstractListModel>
#include "dockbaseproperties.h"

namespace Widgets
{

class Settings;
class PackageManager;
/**
 * @short Model for docks
 *
 * This class is the model that manages the content
 * docks. It is used to anchors the docks as well
 * as providing the information about the files to load.
 *
 * Each item of this model is a DockProperties
 * that is used to control all the parameters
 * related to displayed docks.
 *
 * Modifying this model can be done using
 * - addDock()
 * - removeDock()
 *
 * The first build a DockProperties based
 * on a DockBaseProperties and assign
 * default properties to the new parameters.
 * The second removes a dock based on a
 * DockProperties.
 *
 * This class needs a Settings object to be provided
 * since the models needs to save settings.
 *
 * This class is used in QML context. Accessing
 * it is done using the "viewDocksModel" global object.
 */
class DisplayedDocksModel : public QAbstractListModel
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
public:
    /**
     * @short Model roles
     */
    enum DisplayedDocksRole {
        /**
         * @short Widget role
         */
        DockRole = Qt::UserRole + 1
    };
    /**
     * @short Default constructor
     *
     * @param settings Settings object used to manage settings.
     * @param packageManager PackageManager object used to provide available docks.
     * @param parent parent object.
     */
    explicit DisplayedDocksModel(Settings *settings, PackageManager *packageManager,
                                 QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~DisplayedDocksModel();
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
     * @short Has dock
     *
     * This method is used to check if the model
     * has an instance of a given dock, described
     * by a dock base properties.
     *
     * @param dock the dock to check.
     * @return if the model has an instance of this dock.
     */
    Q_INVOKABLE bool hasDock(Widgets::DockBaseProperties * dock);
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
     * @short Add a dock
     *
     * This method is used to add a dock
     * to the model. The dock to add is
     * caracterized by a DockBaseProperties.
     *
     * Missing properties such as identifier and settings
     * are either provided or added by this method.
     *
     * @param dock the dock to add.
     * @param settings settings of the dock to add.
     * @param identifier identifier of the dock to add (only used during loading).
     */
    void addDock(Widgets::DockBaseProperties *dock,
                 const QVariantMap &settings = QVariantMap(),
                 const QString &identifier = QString());
    /**
     * @short Remove a dock
     *
     * This method is used to remove a dock
     * that is in the model.
     *
     * This method is based on the base properties
     * of the dock to remove.
     *
     * @param dock the dock to remove.
     */
    void removeDock(Widgets::DockBaseProperties *dock);
private:
    class DisplayedDocksModelPrivate;
    /**
     * @short D-pointer
     */
    DisplayedDocksModelPrivate * const d;

};

}

#endif // WIDGETS_DISPLAYEDDOCKSMODEL_H
