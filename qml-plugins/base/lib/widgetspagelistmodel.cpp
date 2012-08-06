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
 * @file displayedpagesmodel.cpp
 * @short Implementation of Widgets::DisplayedPagesModel
 *
 * This file contains the implemetation of the
 * Widgets::DisplayedPagesModel class and the declaration and
 * implementation of Widgets::DisplayedPagesModel::DisplayedPagesModelPrivate
 * and Widgets::WidgetViewModelItem.
 */

#include "widgetspagelistmodel.h"
#include "widgetspagemodel.h"

#include <QtCore/QDebug>

static const char *WIDGETS_GROUP = "widgets";
static const char *WIDGETS_PAGE_COUNT = "pageCount";
static const char *WIDGETS_INITIAL_PAGE = "initialPage";

namespace Widgets
{

/**
 * @internal
 * @short Private class for DisplayedPagesModel
 */
class WidgetsPageListModelPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param settings Settings object used to manage settings.
     * @param packageManager PackageManager object used to provide available widgets.
     * @param parent parent Q-pointer.
     */
    WidgetsPageListModelPrivate(WidgetsPageListModel *parent);
    /**
     * @short Destructor
     */
    ~WidgetsPageListModelPrivate();
    void loadSettings();
    /**
     * @short Slot that watch the pages
     *
     * This slot is connected to DisplayedPagesModel::rowsInserted()
     * and is used to watch if the models has changed,
     * and to emit DisplayedPagesModel::pageRowInserted() if needed.
     *
     * @param parent parent model index.
     * @param start the first row that is new.
     * @param end the last row that is new.
     */
    void slotRowsInserted(const QModelIndex &parent, int start, int end);
    /**
     * @short A list of WidgetViewModelItem
     *
     * This list of WidgetViewModelItem is the
     * internal storage of the model.
     */
    QList<WidgetsPageModel *> items;
    int initialPage;
    int currentPage;
    /**
     * @short %Settings
     */
    Settings *settings;
    GridManager *gridManager;
    /**
     * @short Package manager
     */
    PackageManager *packageManager;
private:
    /**
     * @short Q-pointer
     */
    WidgetsPageListModel *q_ptr;
    Q_DECLARE_PUBLIC(WidgetsPageListModel)
};

WidgetsPageListModelPrivate::WidgetsPageListModelPrivate(WidgetsPageListModel* q):
    q_ptr(q)
{
    settings = 0;
    gridManager = 0;
    packageManager = 0;
    initialPage = -1;
    currentPage = -1;
}

WidgetsPageListModelPrivate::~WidgetsPageListModelPrivate()
{
    // Delete allocated items
    while (!items.isEmpty()) {
        items.takeFirst()->deleteLater();
    }
}

void WidgetsPageListModelPrivate::loadSettings()
{
    Q_Q(WidgetsPageListModel);
    int pageCount = settings->value(WIDGETS_GROUP, WIDGETS_PAGE_COUNT).toInt();
    q->setPageCount(pageCount);
    initialPage = settings->value(WIDGETS_GROUP, WIDGETS_INITIAL_PAGE).toInt();
    currentPage = initialPage;
    emit q->initialPageChanged(initialPage);
    emit q->currentPageChanged(currentPage);
}


////// End of private class //////

WidgetsPageListModel::WidgetsPageListModel(QObject *parent):
    QAbstractListModel(parent), d_ptr(new WidgetsPageListModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(IndexRole, "index");
    roles.insert(PageModelRole, "pageModel");
    setRoleNames(roles);
}

WidgetsPageListModel::WidgetsPageListModel(WidgetsPageListModelPrivate *dd,
                                                   QObject *parent):
    QAbstractListModel(parent), d_ptr(dd)
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(IndexRole, "index");
    roles.insert(PageModelRole, "pageModel");
    setRoleNames(roles);
}

WidgetsPageListModel::~WidgetsPageListModel()
{
}

int WidgetsPageListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const WidgetsPageListModel);
    return d->items.count();
}

int WidgetsPageListModel::count() const
{
    return rowCount();
}

int WidgetsPageListModel::initialPage() const
{
    Q_D(const WidgetsPageListModel);
    return d->initialPage;
}

int WidgetsPageListModel::currentPage() const
{
    Q_D(const WidgetsPageListModel);
    return d->currentPage;
}

Settings * WidgetsPageListModel::settings() const
{
    Q_D(const WidgetsPageListModel);
    return d->settings;
}

GridManager * WidgetsPageListModel::gridManager() const
{
    Q_D(const WidgetsPageListModel);
    return d->gridManager;
}

PackageManager * WidgetsPageListModel::packageManager() const
{
    Q_D(const WidgetsPageListModel);
    return d->packageManager;
}

QVariant WidgetsPageListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const WidgetsPageListModel);
    if (index.row() < 0 or index.row() >= rowCount())
    {
        return QVariant();
    }

    WidgetsPageModel *item = d->items.at(index.row());
    switch(role) {
    case IndexRole:
        return item->pageIndex();
        break;
    case PageModelRole:
        return QVariant::fromValue(item);
        break;
    default:
        return QVariant();
        break;
    }
}

bool WidgetsPageListModel::addWidget(int pageIndex,
                                     WidgetBaseProperties *widget,
                                     Widgets::GridManager *gridManager,
                                     const QVariantMap &settings,
                                     const QString &identifier)
{
    Q_D(WidgetsPageListModel);
    if (pageIndex < 0 || pageIndex >= rowCount()) {
        return false;
    }

    return d->items[pageIndex]->addWidget(widget, gridManager, settings, identifier);
}

void WidgetsPageListModel::setSettings(Settings *settings)
{
    Q_D(WidgetsPageListModel);
    if (d->settings != settings) {
        d->settings = settings;
        emit settingsChanged();
        d->loadSettings();
    }
}

void WidgetsPageListModel::setGridManager(GridManager *gridManager)
{
    Q_D(WidgetsPageListModel);
    if (d->gridManager != gridManager) {
        d->gridManager = gridManager;
        emit gridManagerChanged();
    }
}

void WidgetsPageListModel::setPackageManager(PackageManager *packageManager)
{
    Q_D(WidgetsPageListModel);
    if (d->packageManager != packageManager) {
        d->packageManager = packageManager;
        emit packageManagerChanged();
    }

    if (d->packageManager != 0) {
        foreach (WidgetsPageModel *item, d->items) {
            item->setPackageManager(d->packageManager);
        }
    }
}

void WidgetsPageListModel::setCurrentPage(int currentPage)
{
    Q_D(WidgetsPageListModel);
    if (d->currentPage != currentPage) {
        d->currentPage = currentPage;
        emit currentPageChanged(currentPage);
    }
}

void WidgetsPageListModel::setPageCount(int count)
{
    if (rowCount() < count) {
        for(int i = rowCount(); i < count; i++) {
            addPage();
        }
    } else if (rowCount() > count) {
        for(int i = count; i < rowCount(); i++) {
            removePage();
        }
    }
}

void WidgetsPageListModel::addPage()
{
    Q_D(WidgetsPageListModel);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    WidgetsPageModel *item = new WidgetsPageModel(this);
    item->setPackageManager(d->packageManager);
    item->setPageIndex(rowCount());

    d->items.append(item);

    emit countChanged(rowCount());
    endInsertRows();
}

void WidgetsPageListModel::removePage()
{
    Q_D(WidgetsPageListModel);

    if (rowCount() == 0) {
        return;
    }

    beginRemoveRows(QModelIndex(), rowCount() - 1, rowCount() - 1);

    WidgetsPageModel *item = d->items.takeLast();
    item->deleteLater();

    emit countChanged(rowCount());
    endRemoveRows();
}

}

#include "moc_widgetspagelistmodel.cpp"