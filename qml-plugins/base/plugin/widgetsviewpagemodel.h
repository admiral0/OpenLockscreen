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
 * @file displayedpagewidgetsmodel.h
 * @short Definition of Widgets::DisplayedPageWidgetsModel
 *
 * This file contains the definition of the
 * Widgets::DisplayedPageWidgetsModel class.
 */

#ifndef WIDGETS_WIDGETSVIEWPAGEMODEL_H
#define WIDGETS_WIDGETSVIEWPAGEMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QRect>
#include "widgetproperties.h"

namespace Widgets
{

class Settings;
class PackageManager;
/**
 * @short Model for displayed widget page
 *
 * This class is the model that manages the content
 * of a page, like the type, position, size and
 * parameters of the displayed widgets in a page.
 *
 * Each item of this model is a WidgetProperties
 * that is used to control all the parameters
 * related to displayed widgets.
 *
 * Modifying this model can be done using
 * - addWidget()
 * - removeWidget()
 * - updateWidget()
 *
 * The first build a WidgetProperties based
 * on a WidgetBaseProperties and assign
 * given properties to the new parameters.
 * The second removes a widget based on a
 * WidgetProperties. The last one is used
 * to update a widget based on it's index
 * and position / size parameters.
 *
 * This class is used as a bridge between
 * all sources that can change the position of
 * a widget and the view, that places the widgets
 * according to this model.
 *
 * This class needs a Settings object to be provided
 * since the models needs to save settings.
 */
class DisplayedPageWidgetsModel : public QAbstractListModel
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
    /**
     * @short Index of this page
     *
     * This property is mainly used in QML context
     * and is used to retrieve the index of this page.
     */
    Q_PROPERTY(int pageIndex READ pageIndex CONSTANT)
public:
    /**
     * @short Model roles
     */
    enum DisplayedPageWidgetsRole {
        /**
         * @short Widget role
         */
        WidgetRole = Qt::UserRole + 1
    };
    /**
     * @short Default constructor
     *
     * @param pageIndex index of this page.
     * @param settings Settings object used to manage settings.
     * @param packageManager PackageManager object used to provide available widgets.
     * @param parent parent object.
     */
    explicit DisplayedPageWidgetsModel(int pageIndex = -1,
                                       Settings *settings = 0,
                                       PackageManager *packageManager = 0,
                                       QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~DisplayedPageWidgetsModel();
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
     * @short Index of this page
     *
     * This method is used to retrieve the
     * index of this page.
     *
     * @return the index of this page.
     */
    int pageIndex() const;
    /**
     * @short Properties of a widget
     *
     * This method is used to have a direct access
     * to the properties of a widget at a given
     * index.
     *
     * @param index index to retrieve the widget.
     * @return the widget at the given index.
     */
    Q_INVOKABLE Widgets::WidgetProperties * widget(int index) const;
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
     * @short Add a widget
     *
     * This method is used to add a widget
     * to the model. The widget to add is
     * caracterized by a WidgetBaseProperties.
     *
     * Missing properties such as position and
     * dimensions, identifier, and settings
     * are either provided or added by this method.
     *
     * @param widget the widget to add.
     * @param x the x coordinate of the widget to add.
     * @param y the y coordinate of the widget to add.
     * @param width the width of the widget to add.
     * @param height the height of the widget to add.
     * @param settings settings of the widget to add.
     * @param identifier identifier of the widget to add (only used during loading).
     * @param z the z coordinate of the widget to add (only used during loading).
     */
    void addWidget(Widgets::WidgetBaseProperties *widget,
                   int x = 0, int y = 0,
                   int width = 0, int height = 0,
                   const QVariantMap &settings = QVariantMap(),
                   const QString &identifier = QString(), int z = -1);
    /**
     * @short Remove a widget
     *
     * This method is used to remove a widget
     * that is in the model.
     *
     * @param widget the widget to remove.
     */
    void removeWidget(Widgets::WidgetProperties *widget);
    /**
     * @short Update a widget
     *
     * Update the position and dimensions
     * of a widget.
     *
     * @param identifier identifier of the widget to update.
     * @param x new x coordinate.
     * @param y new y coordinate.
     * @param width new width.
     * @param height new height.
     */
    void updateWidget(const QString &identifier, int x, int y, int width, int height);
private:
    class DisplayedPageWidgetsModelPrivate;
    /**
     * @short D-pointer
     */
    DisplayedPageWidgetsModelPrivate * const d;
};

}

Q_DECLARE_METATYPE(Widgets::DisplayedPageWidgetsModel*)

#endif // WIDGETS_WIDGETSVIEWPAGEMODEL_H
