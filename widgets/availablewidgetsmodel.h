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
 * @file availablewidgetsmodel.h
 * @short Definition of Widgets::AvailableWidgetsModel
 *
 * This file contains the definition of the
 * Widgets::AvailableWidgetsModel class.
 */

#ifndef WIDGET_AVAILABLEWIDGETSMODEL_H
#define WIDGET_AVAILABLEWIDGETSMODEL_H

#include <QtCore/QAbstractListModel>

namespace Widgets
{

class WidgetBaseProperties;
/**
 * @short Model for available widgets
 *
 * This class is the model that describes the
 * widgets that are available. It is used in the
 * widgets selector that is used to add new
 * widgets.
 *
 * Each item of this model is a WidgetBaseProperties
 * that is used to provide all informations about
 * a widget to be created, as well as package information
 * that can be used for grouping.
 *
 * Modifying this model can be done using addWidget(),
 * that simply append a widget described by a
 * WidgetBaseProperties and it's package name to the
 * end of the model.
 *
 * This class is used in QML context. Accessing
 * it is done using the "availableWidgetsModel" global object.
 */
class AvailableWidgetsModel : public QAbstractListModel
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
    enum AvailableWidgetsRole {
        /**
         * @short Widget role
         */
        WidgetRole = Qt::UserRole + 1 ,
        /**
         * @short Package role
         */
        PackageRole
    };
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit AvailableWidgetsModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~AvailableWidgetsModel();
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
     * @short Add a widget
     *
     * This method is used to add a widget
     * to the model. The widget to add is
     * caracterized by a WidgetBaseProperties.
     *
     * This WidgetBaseProperties is used to
     * provide default parameters for the
     * widget to be displayed.
     *
     * This method also use a package name
     * that is used for grouping.
     *
     * @param package name of the package that the widget belongs.
     * @param widget the widget to add.
     */
    void addWidget(const QString &package, WidgetBaseProperties *widget);
private:
    class AvailableWidgetsModelPrivate;
    /**
     * @short D-pointer
     */
    AvailableWidgetsModelPrivate * const d;
};

}

#endif // WIDGET_AVAILABLEWIDGETSMODEL_H
