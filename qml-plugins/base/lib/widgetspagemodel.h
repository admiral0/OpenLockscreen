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
 * @file widgetspagemodel.h
 * @short Definition of Widgets::WidgetsPageModel
 */

#ifndef WIDGETS_WIDGETSVIEWPAGEMODEL_H
#define WIDGETS_WIDGETSVIEWPAGEMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QRect>
#include "widgetproperties.h"

class QDeclarativeContext;
namespace Widgets
{

class GridManager;
class Settings;
class WidgetProviderBase;
class WidgetsPageModelPrivate;
/**
 * @short Model for a widget page
 *
 * This class is the model that manages the content
 * of a page, like the type, position, size and
 * parameters of the displayed widgets in a page.
 *
 * Each item of this model is a Widgets::WidgetProperties
 * that is used to control all the parameters
 * related to displayed widgets.
 *
 * Modifying this model can be done using
 * - addWidget()
 * - removeWidget()
 *
 * The first build a Widgets::WidgetProperties based
 * on a Widgets::WidgetBaseProperties and assign
 * given properties to the new parameters.
 * The second removes a widget based on a
 * Widgets::WidgetProperties.
 *
 * Please note that Widget::WidgetProperties objects
 * created with addWidget are automatically linked to
 * the real QML widget, and also to settings. If the properties
 * this object are changed, they will automatically be reflected
 * in a graphical change and saved.
 *
 * This class save settings as XML files. They are stored as
 * settings-widget-\<page index\>.xml, using QDesktopServices::DataLocation.
 * Loading the settings is done when calling load(). Saving is
 * managed automatically, when widgets changes, are added or
 * removed.
 */
class WidgetsPageModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Page index
     */
    Q_PROPERTY(int pageIndex READ pageIndex NOTIFY pageIndexChanged)
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum WidgetsPageModelRole {
        /**
         * @short Widget role
         */
        WidgetRole = Qt::UserRole + 1
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit WidgetsPageModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~WidgetsPageModel();
    /**
     * @brief Set provider
     * @param provider provider to set.
     */
    void setProvider(WidgetProviderBase *provider);
    /**
     * @brief Page index
     * @return page index.
     */
    int pageIndex() const;
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
     * @brief Set page index
     * @param index page index.
     */
    void setPageIndex(int index);
    /**
     * @brief Load
     *
     * Load settings from the XML file associated to
     * this page.
     */
    void load();
    /**
     * @short Add a widget
     * @param widget base properties of the widget to add.
     * @param gridManager grid manager.
     * @param settings widget settings.
     * @param identifier widget identifier.
     * @return if the operation is successful.
     */
    bool addWidget(Widgets::WidgetBaseProperties *widget,
                   Widgets::GridManager *gridManager,
                   const QVariantMap &settings = QVariantMap(),
                   const QString &identifier = QString());
    /**
     * @short Add a widget
     * @param widget base properties of the widget to add.
     * @param x xcoordinate.
     * @param y y coordinate.
     * @param z z coordinate.
     * @param width width.
     * @param height height.
     * @param settings widget settings.
     * @param identifier widget identifier.
     * @return if the operation is successful.
     */
    bool addWidget(Widgets::WidgetBaseProperties *widget,
                   int x, int y, int z,
                   int width, int height,
                   const QVariantMap &settings = QVariantMap(),
                   const QString &identifier = QString());
    /**
     * @brief Add a widget
     * @param widget the widget to add.
     * @return if the operation is successful.
     */
    bool addWidget(Widgets::WidgetProperties *widget);
    /**
     * @short Remove a widget
     * @param widget widget to remove.
     * @return if the operation is successful.
     */
    bool removeWidget(Widgets::WidgetProperties *widget);
public Q_SLOTS:

//    void relayout(Widgets::GridManager *gridManager);

//    void addWidget(Widgets::WidgetBaseProperties *widget,
//                   int x = 0, int y = 0,
//                   int width = 0, int height = 0,
//                   const QVariantMap &settings = QVariantMap(),
//                   const QString &identifier = QString(), int z = -1);
//    void updateWidget(const QString &identifier, int x, int y, int width, int height);
Q_SIGNALS:
    /**
     * @brief Page index changed
     */
    void pageIndexChanged();
    /**
     * @short Count changed
     */
    void countChanged();
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    explicit WidgetsPageModel(WidgetsPageModelPrivate *dd, QObject *parent = 0);
    /**
     * @brief Reimplementation of event
     *
     * This reimplementation is done to enable a
     * queued save.
     *
     * @param event event to react to.
     * @return if the event succeeded.
     */
    virtual bool event(QEvent *event);
    /**
     * @short D-pointer
     */
    const QScopedPointer<WidgetsPageModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(WidgetsPageModel)
    Q_PRIVATE_SLOT(d_func(), void requestSave())
};

}

Q_DECLARE_METATYPE(Widgets::WidgetsPageModel*)

#endif // WIDGETS_WIDGETSVIEWPAGEMODEL_H
