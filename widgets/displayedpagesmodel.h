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
 * @file displayedpagesmodel.h
 * @short Definition of Widgets::DisplayedPagesModel
 *
 * This file contains the definition of the
 * Widgets::DisplayedPagesModel class.
 */

#ifndef WIDGETS_DISPLAYEDPAGESMODEL_H
#define WIDGETS_DISPLAYEDPAGESMODEL_H

#include <QAbstractListModel>
#include "displayedpagewidgetsmodel.h"

namespace Widgets
{

class Settings;
class PackageManager;
/**
 * @short Model for widgets page
 *
 * This class is the base model for the widgets
 * view. This model simply controls the number
 * of pages that this view have, without managing
 * the content of these pages.
 *
 * Each item of this model is a ViewWidgetPageModel
 * that is used to control the content of each page,
 * with an index that is used to know the index of
 * the current page.
 *
 * Modifying this model can be done using
 * - addPage()
 * - removePage()
 *
 * The first method appends a page to the model
 * and the last removes the last page.
 *
 * This class needs a Settings object to be provided
 * since the models needs to save settings.
 *
 * This class is used in QML context. Accessing
 * it is done using the "displayedPagesModel" global object.
 */
class DisplayedPagesModel : public QAbstractListModel
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
    enum DisplayedPagesRole {
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
     *
     * @param settings Settings object used to manage settings.
     * @param packageManager PackageManager object used to provide available widgets.
     * @param parent parent object.
     */
    explicit DisplayedPagesModel(Settings *settings, PackageManager *packageManager,
                                 QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~DisplayedPagesModel();
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
     * @short Direct access to page model
     *
     * This method is used to have a direct access
     * to a page model.
     *
     * @param index index of the page to retrieve.
     * @return the page model at the given index.
     */
    Q_INVOKABLE Widgets::DisplayedPageWidgetsModel * pageModel(int index) const;
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
    /**
     * @short Row inserted in a page
     *
     * Notify that in a page, rows
     * was inserted.
     *
     * @param page the page that changed.
     * @param parent parent model index.
     * @param start the first row that is new.
     * @param end the last row that is new.
     */
    void pageRowInserted(DisplayedPageWidgetsModel * page,
                         const QModelIndex &parent, int start, int end);
public Q_SLOTS:
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
private:
    class DisplayedPagesModelPrivate;
    /**
     * @short D-pointer
     */
    DisplayedPagesModelPrivate * const d;

    Q_PRIVATE_SLOT(d, void slotRowsInserted(const QModelIndex &parent, int start, int end))
};

}

#endif // WIDGETS_DISPLAYEDPAGESMODEL_H
