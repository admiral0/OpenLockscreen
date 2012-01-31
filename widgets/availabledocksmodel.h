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
 * @file availabledocksmodel.h
 * @short Definition of Widgets::AvailableDocksModel
 *
 * This file contains the definition of the
 * Widgets::AvailableDocksModel class.
 */

#ifndef WIDGET_AVAILABLEDOCKSMODEL_H
#define WIDGET_AVAILABLEDOCKSMODEL_H

#include <QtCore/QAbstractListModel>

namespace Widgets
{

class DockBaseProperties;
/**
 * @short Model for available docks
 *
 * This class is the model that describes the
 * docks that are available. It is used in the
 * docks selector that is used to manage the
 * displayed docks.
 *
 * Each item of this model is a DockBaseProperties
 * that is used to provide all informations about
 * a widget to be created, as well as package information
 * that can be used for grouping.
 *
 * This model also provides information about the currenlty
 * displayed docks. It can be done by checking if the
 * dock is enabled.
 *
 * Modifying this model can be done using addDock(),
 * that simply append a widget described by a
 * DockBaseProperties and it's package name to the
 * end of the model.
 *
 * This class is used in QML context. Accessing
 * it is done using the "dockSelectorModel" global object.
 */
class AvailableDocksModel : public QAbstractListModel
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
    enum AvailableDocksRole {
        /**
         * @short Dock role
         */
        DockRole = Qt::UserRole + 1,
        /**
         * @short Package role
         */
        PackageRole,
        /**
         *@short If the dock is enabled
         */
        EnabledRole
    };
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit AvailableDocksModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~AvailableDocksModel();
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
public slots:
    /**
     * @short Add a dock
     *
     * This method is used to add a dock
     * to the model. The dock to add is
     * caracterized by a DockBaseProperties.
     *
     * This DockBaseProperties is used to
     * provide default parameters for the
     * dock to be displayed.
     *
     * This method also use a package name
     * that is used for grouping.
     *
     * @param package name of the package that the dock belongs.
     * @param dock the dock to add.
     */
    void addDock(const QString &package, DockBaseProperties *dock);
private:
    class AvailableDocksModelPrivate;
    /**
     * @short D-pointer
     */
    AvailableDocksModelPrivate * const d;
};

}

#endif // WIDGET_AVAILABLEDOCKSMODEL_H
