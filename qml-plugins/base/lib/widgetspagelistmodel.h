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
 * @file widgetspagelistmodel.h
 * @short Definition of Widgets::WidgetsPageListModel
 */

#ifndef WIDGETS_WIDGETSVIEWPAGELISTMODEL_H
#define WIDGETS_WIDGETSVIEWPAGELISTMODEL_H

#include <QtCore/QAbstractListModel>

#include "widgetspagemodel.h"
#include "settings.h"
#include "gridmanager.h"

namespace Widgets
{

class ProviderManager;
class WidgetsPageListModelPrivate;
/**
 * @short Base model for widgets
 *
 * This class is the base model for the widgets
 * view. This model simply controls the number
 * of pages that this view have, without managing
 * the content of these pages.
 *
 * Each item of this model is a Widgets::WidgetPageModel
 * that is used to control the content of each page,
 * with an index that is used to know the index of
 * the current page.
 *
 * Modifying this model can be done using
 * - addPage()
 * - removePage()
 * - setPageCount()
 *
 * The first method appends a page to the model
 * the second removes the last page. The last one
 * adjust the number of pages, adding or removing
 * them.
 *
 * This model is also used to manage widgets that
 * are contained in the pages. The following methods
 * are used
 * - addWidget()
 * - removeWidget()
 * The first add a widget to a given page, by providing
 * the necessary properties. The second remove a widget
 * on a given page.
 *
 * This class needs a Widgets::Settings object to be provided
 * since the models needs to save settings.
 */
class WidgetsPageListModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    /**
     * @short Initial page
     */
    Q_PROPERTY(int initialPage READ initialPage NOTIFY initialPageChanged)
    /**
     * @short Current Page
     */
    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    /**
     * @short %Settings
     */
    Q_PROPERTY(Widgets::Settings * settings READ settings WRITE setSettings NOTIFY settingsChanged)
public:
    /**
     * @short Model roles
     */
    enum WidgetsPageListModelRole {
        /**
         * @short Index role
         */
        IndexRole = Qt::UserRole + 1 ,
        /**
         * @short Page model role
         */
        PageModelRole
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit WidgetsPageListModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~WidgetsPageListModel();
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
     * @brief Initial page
     * @return initial page.
     */
    int initialPage() const;
    /**
     * @brief Current page
     * @return current page.
     */
    int currentPage() const;
    /**
     * @brief %Settings
     * @return settings.
     */
    Settings * settings() const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /**
     * @short Add widget
     * @param pageIndex page index.
     * @param widget base properties of the widget to add.
     * @param gridManager grid manager.
     * @param settings widget settings.
     * @param identifier widget identifier.
     * @return if the operation is successful.
     */
    Q_INVOKABLE bool addWidget(int pageIndex,
                               Widgets::WidgetBaseProperties *widget,
                               Widgets::GridManager *gridManager,
                               const QVariantHash &settings = QVariantHash(),
                               const QString &identifier = QString());
    /**
     * @short Remove widget
     * @param pageIndex page index.
     * @param widget widget to remove.
     * @return if the operation is successful.
     */
    Q_INVOKABLE bool removeWidget(int pageIndex, Widgets::WidgetProperties *widget);
    /**
     * @brief Set the provider manager
     *
     * This method is called to set the current provider manager.
     * It should not be called from a QML context, but be called
     * when the plugin is loaded, to set the provider to the global
     * provider.
     *
     * @param providerManager
     */
    void setProviderManager(ProviderManager *providerManager);
Q_SIGNALS:
    /**
     * @short Count changed
     */
    void countChanged();
    /**
     * @brief Initial page changed
     */
    void initialPageChanged();
    /**
     * @brief Current page changed
     */
    void currentPageChanged();
    /**
     * @brief Settings changed
     */
    void settingsChanged();
public Q_SLOTS:
    /**
     * @brief Set settings
     * @param settings settings.
     */
    void setSettings(Settings *settings);
    /**
     * @brief Set current page
     * @param currentPage current page.
     */
    void setCurrentPage(int currentPage);
    /**
     * @short Set page count
     *
     * This method is used to
     * set the number of pages.
     * It will automaticall add needed
     * pages or remove unused pages.
     *
     * @param count the number of pages to set.
     */
    void setPageCount(int count);
    /**
     * @short Add a page
     *
     * This method is used to append a page
     * at the end of the model.
     */
    void addPage();
    /**
     * @short Remove a page
     *
     * This method is used to remove the last
     * page of the model.
     */
    void removePage();
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    WidgetsPageListModel(WidgetsPageListModelPrivate *dd, QObject *parent);
    /**
     * @short D-pointer
     */
    const QScopedPointer<WidgetsPageListModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(WidgetsPageListModel)
    Q_PRIVATE_SLOT(d_func(), void refreshProvider())
};

}

#endif // WIDGETS_WIDGETSVIEWPAGELISTMODEL_H
