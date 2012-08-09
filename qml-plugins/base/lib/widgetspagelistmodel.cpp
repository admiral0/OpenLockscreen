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
 * @file widgetspagelistmodel.cpp
 * @short Implementation of Widgets::WidgetsPageListModel
 */


#include "widgetspagelistmodel.h"
#include "widgetspagemodel.h"

#include "providermanager.h"

#include <QtCore/QDebug>

/**
 * @brief WIDGETS_GROUP
 *
 * Used in Widgets::WidgetsPageListModel.
 */
static const char *WIDGETS_GROUP = "widgets";
/**
 * @brief WIDGETS_PAGE_COUNT
 *
 * Used in Widgets::WidgetsPageListModel.
 */
static const char *WIDGETS_PAGE_COUNT = "pageCount";
/**
 * @brief WIDGETS_INITIAL_PAGE
 *
 * Used in Widgets::WidgetsPageListModel.
 */
static const char *WIDGETS_INITIAL_PAGE = "initialPage";

namespace Widgets
{

/**
 * @internal
 * @short Private class for Widgets::WidgetsPageListModel
 */
class WidgetsPageListModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     *
     * @param parent parent Q-pointer.
     */
    WidgetsPageListModelPrivate(WidgetsPageListModel *parent);
    /**
     * @internal
     * @short Destructor
     */
    ~WidgetsPageListModelPrivate();
    /**
     * @internal
     * @brief Refresh the provider
     *
     * This method is called when the provider has changed.
     * It sends the new provider to all the pages.
     */
    void refreshProvider();
    /**
     * @internal
     * @brief Load settings
     *
     * This method is only used to load settings related
     * to the number of pages.
     */
    void loadSettings();
    /**
     * @internal
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
     * @internal
     * @short Items
     */
    QList<WidgetsPageModel *> items;
    /**
     * @internal
     * @brief Initial page
     */
    int initialPage;
    /**
     * @internal
     * @brief Current page
     */
    int currentPage;
    /**
     * @internal
     * @short %Settings
     */
    Settings *settings;
//    GridManager *gridManager;
    /**
     * @internal
     * @short Provider manager
     */
    ProviderManager *providerManager;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    WidgetsPageListModel *q_ptr;
    Q_DECLARE_PUBLIC(WidgetsPageListModel)
};

WidgetsPageListModelPrivate::WidgetsPageListModelPrivate(WidgetsPageListModel* q):
    q_ptr(q)
{
    settings = 0;
//    gridManager = 0;
    providerManager = 0;
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

void WidgetsPageListModelPrivate::refreshProvider()
{
    if (!providerManager) {
        return;
    }
    if (!providerManager->provider()) {
        return;
    }

    foreach (WidgetsPageModel *item, items) {
        item->setProvider(providerManager->provider());
    }
}

void WidgetsPageListModelPrivate::loadSettings()
{
    Q_Q(WidgetsPageListModel);
    int pageCount = settings->value(WIDGETS_GROUP, WIDGETS_PAGE_COUNT).toInt();
    q->setPageCount(pageCount);
    initialPage = settings->value(WIDGETS_GROUP, WIDGETS_INITIAL_PAGE).toInt();
    currentPage = initialPage;
    emit q->initialPageChanged();
    emit q->currentPageChanged();
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

//GridManager * WidgetsPageListModel::gridManager() const
//{
//    Q_D(const WidgetsPageListModel);
//    return d->gridManager;
//}

QVariant WidgetsPageListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const WidgetsPageListModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
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
                                     const QVariantHash &settings,
                                     const QString &identifier)
{
    Q_D(WidgetsPageListModel);
    if (pageIndex < 0 || pageIndex >= rowCount()) {
        return false;
    }

    return d->items[pageIndex]->addWidget(widget, gridManager, settings, identifier);
}

bool WidgetsPageListModel::removeWidget(int pageIndex, WidgetProperties *widget)
{
    Q_D(WidgetsPageListModel);
    if (pageIndex < 0 || pageIndex >= rowCount()) {
        return false;
    }

    return d->items[pageIndex]->removeWidget(widget);
}

void WidgetsPageListModel::setProviderManager(ProviderManager *providerManager)
{
    Q_D(WidgetsPageListModel);
    if (d->providerManager != providerManager) {
        d->providerManager = providerManager;

        connect(d->providerManager, SIGNAL(providerChanged()), this, SLOT(refreshProvider()));
    }
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

//void WidgetsPageListModel::setGridManager(GridManager *gridManager)
//{
//    Q_D(WidgetsPageListModel);
//    if (d->gridManager != gridManager) {
//        d->gridManager = gridManager;
//        emit gridManagerChanged();
//    }
//}

void WidgetsPageListModel::setCurrentPage(int currentPage)
{
    Q_D(WidgetsPageListModel);
    if (d->currentPage != currentPage) {
        d->currentPage = currentPage;
        emit currentPageChanged();
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

    if (d->providerManager) {
        item->setProvider(d->providerManager->provider());
    }
    item->setPageIndex(rowCount());

    d->items.append(item);

    emit countChanged();
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

    emit countChanged();
    endRemoveRows();
}

}

#include "moc_widgetspagelistmodel.cpp"
