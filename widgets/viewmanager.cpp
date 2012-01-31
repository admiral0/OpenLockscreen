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
 * @file viewmanager.cpp
 * @short Implementation of Widgets::ViewManager
 *
 * This file contains the implemetation of the
 * Widgets::ViewManager class and the declaration and
 * implementation of Widgets::ViewManager::ViewManagerPrivate.
 */

#include "viewmanager.h"
#include "displayedpagewidgetsmodel.h"
#include "settingswrapper.h"

#include <QtCore/QSize>
#include <QtCore/qmath.h>
#include <QtDeclarative/QDeclarativeItem>
#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @short Private class for ViewManager
 */
class ViewManager::ViewManagerPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param settingsWrapper SettingsWrapper object used provide settings.
     * @param displayedPagesModel DisplayedPagesModel object used to provide the models of the view.
     * @param parent parent Q-pointer.
     */
    ViewManagerPrivate(SettingsWrapper *settingsWrapper, DisplayedPagesModel *displayedPagesModel,
                       ViewManager *parent);
    /**
     * @short Recompute the grid count
     *
     * This method is used to recompute the grid count.
     * It should be called if the view size has changed
     * or if the grid cell parameters has changed.
     */
    void recomputeGridCount();
    /**
     * @short Locked changed
     *
     * This slot is connected on ViewManager::lockedChanged
     * signal. It is used to manage draggers. When
     * the view is unlocked, draggers should be created
     * and when the view is locked, they should be detroyed.
     *
     * @param locked is the widgets are locked.
     */
    void slotLockedChanged(bool locked);
    /**
     * @short Row inserted in a page
     *
     * This slot is used to manage the insertion
     * of new widget in a page, and used to add
     * new draggers if needed.
     *
     * @param page the ViewWidgetsPageModel that has changed.
     * @param parent parent model index.
     * @param start the first row that is new.
     * @param end the last row that is new.
     */
    void slotPageRowInserted(DisplayedPageWidgetsModel *page,
                             const QModelIndex &parent, int start, int end);
    /**
     * @short If the widgets are locked
     */
    bool locked;
    /**
     * @short %Settings wrapper
     */
    SettingsWrapper * const settingsWrapper;
    /**
     * @short View widgets model
     */
    DisplayedPagesModel * const displayedPagesModel;
    /**
     * @short View size
     */
    QSize viewSize;
    /**
     * @short Grid size
     */
    QSize gridSize;
    /**
     * @short Current displayed page index
     */
    int currentPageIndex;
    /**
     * @short Current dragged widget
     *
     * The current dragged widget is
     * identified by it's identifier.
     */
    QString currentDraggedWidget;
    /**
     * @short Highlight rectangle
     */
    QRect highlightRect;
    /**
     * @short Registered draggers
     *
     * The draggers are stored using a map that associates
     * the widget to a declarative item that is
     * the dragger.
     */
    QMap<WidgetProperties *, QDeclarativeItem *> registeredDraggers;

private:
    /**
     * @short Q-pointer
     */
    ViewManager * const q;
};

ViewManager::ViewManagerPrivate::ViewManagerPrivate(SettingsWrapper *settingsWrapper,
                                                    DisplayedPagesModel *displayedPagesModel,
                                                    ViewManager *parent):
    settingsWrapper(settingsWrapper), displayedPagesModel(displayedPagesModel), q(parent)
{
    locked = true;
    viewSize = QSize(0, 0);
    gridSize = QSize(0, 0);
    currentDraggedWidget = "";
    highlightRect = QRect(0, 0, 0, 0);
    currentPageIndex = -1;
}

void ViewManager::ViewManagerPrivate::recomputeGridCount()
{
    int cellWidth = settingsWrapper->gridCellWidth();
    int cellHeight = settingsWrapper->gridCellHeight();
    int cellHMargin = settingsWrapper->gridCellHorizontalMargin();
    int cellVMargin = settingsWrapper->gridCellVerticalMargin();

    int newGridWidth = (viewSize.width() + cellHMargin) / (cellWidth + cellHMargin);
    int newGridHeight = (viewSize.height() + cellVMargin) / (cellHeight + cellVMargin);


    if (newGridWidth != gridSize.width()) {
        gridSize.setWidth(newGridWidth);
        emit q->gridWidthChanged(newGridWidth);
    }

    if (newGridHeight  != gridSize.height()) {
        gridSize.setHeight(newGridHeight );
        emit q->gridHeightChanged(newGridHeight);
    }
}

void ViewManager::ViewManagerPrivate::slotLockedChanged(bool locked)
{
    if(locked) {
        // When the view is locked, all draggers should be destroyed
        QMapIterator<WidgetProperties *, QDeclarativeItem *> iterator =
                QMapIterator<WidgetProperties *, QDeclarativeItem *>(registeredDraggers);
        while (iterator.hasNext()) {
            iterator.next();
            QDeclarativeItem *item = iterator.value();
            registeredDraggers.remove(iterator.key());
            item->deleteLater();
        }

        q->setCurrentDraggedWidget("");
    } else {
        // For each item in the current page, a dragger should
        // be created
        DisplayedPageWidgetsModel * pageModel = displayedPagesModel->pageModel(currentPageIndex);
        for (int i = 0; i < pageModel->rowCount(); i++) {
            emit q->requestCreateDragger(pageModel->widget(i));
        }
    }
}

void ViewManager::ViewManagerPrivate::slotPageRowInserted(DisplayedPageWidgetsModel * page,
                                                          const QModelIndex &parent,
                                                          int start, int end)
{
    Q_UNUSED(parent)
    if(locked) {
        return;
    }

     if(currentPageIndex != page->pageIndex()) {
         return;
     }

    if(start == end) {
        emit q->requestCreateDragger(page->widget(start));
    }
}

////// End of private class //////

ViewManager::ViewManager(SettingsWrapper *settingsWrapper,
                         DisplayedPagesModel *displayedPagesModel,
                         QObject *parent):
    QObject(parent), d(new ViewManagerPrivate(settingsWrapper, displayedPagesModel, this))
{
    connect(this, SIGNAL(lockedChanged(bool)), this, SLOT(slotLockedChanged(bool)));
    connect(displayedPagesModel,
            SIGNAL(pageRowInserted(DisplayedPageWidgetsModel* ,QModelIndex ,int ,int)),
            this,
            SLOT(slotPageRowInserted(DisplayedPageWidgetsModel* ,QModelIndex ,int ,int)));
    setCurrentPageIndex(d->settingsWrapper->pageInitialIndex());
}

ViewManager::~ViewManager()
{
    delete d;
}

bool ViewManager::isLocked() const
{
    return d->locked;
}

int ViewManager::gridWidth() const
{
    return d->gridSize.width();
}

int ViewManager::gridHeight() const
{
    return d->gridSize.height();
}

int ViewManager::currentPageIndex() const
{
    return d->currentPageIndex;
}

QString ViewManager::currentDraggedWidget() const
{
    return d->currentDraggedWidget;
}

QRect ViewManager::highlightRect() const
{
    return d->highlightRect;
}

QPoint ViewManager::computeWidgetPosition(int widgetX, int widgetY) const
{
    int cellWidth = d->settingsWrapper->gridCellWidth();
    int cellHeight = d->settingsWrapper->gridCellWidth();
    int cellHMargin = d->settingsWrapper->gridCellHorizontalMargin();
    int cellVMargin = d->settingsWrapper->gridCellVerticalMargin();

    float xRatio = (float) (widgetX + cellHMargin) / (cellWidth + cellHMargin);
    int x = qRound(xRatio) * (cellWidth + cellHMargin);

    float yRatio = (float) (widgetY + cellVMargin) / (cellHeight + cellVMargin);
    int y = qRound(yRatio) * (cellHeight + cellVMargin);

    return QPoint(x, y);
}

QSize ViewManager::computeWidgetSize(int widgetWidth, int widgetHeight) const
{
    int cellWidth = d->settingsWrapper->gridCellWidth();
    int cellHeight = d->settingsWrapper->gridCellWidth();
    int cellHMargin = d->settingsWrapper->gridCellHorizontalMargin();
    int cellVMargin = d->settingsWrapper->gridCellVerticalMargin();

    float rowCount = ((float) widgetWidth + (float) cellHMargin) /
                     ((float) cellWidth + (float) cellHMargin);
    float columnCount = ((float) widgetHeight + (float) cellVMargin) /
                        ((float) cellHeight + (float) cellVMargin);

    int width = qCeil(rowCount) * cellWidth + rowCount * cellHMargin;
    int height = qCeil(columnCount) * cellHeight + columnCount * cellVMargin;

    return QSize(width, height);
}

QRect ViewManager::availableRect(int widgetWidth, int widgetHeight) const
{
    int cellWidth = d->settingsWrapper->gridCellWidth();
    int cellHeight = d->settingsWrapper->gridCellWidth();
    int cellHMargin = d->settingsWrapper->gridCellHorizontalMargin();
    int cellVMargin = d->settingsWrapper->gridCellVerticalMargin();

    QList<QRect> widgetsRects;
    DisplayedPageWidgetsModel * currentPage =
            d->displayedPagesModel->pageModel(d->currentPageIndex);

    for (int i = 0; i < currentPage->count() ; i++) {
        WidgetProperties * widget = currentPage->widget(i);
        QRect widgetRect = QRect(widget->x(), widget->y(), widget->width(), widget->height());
        widgetsRects.append(widgetRect);
    }

    int x = 0;
    int y = 0;
    bool found = false;
    QSize correctSize = computeWidgetSize(widgetWidth, widgetHeight);
    int removedWidth = qCeil((float) correctSize.width()
                             / ((float) cellWidth + (float) cellHMargin)) - 1;
    int removedHeight = qCeil((float) correctSize.height()
                             / ((float) cellHeight + (float) cellVMargin)) - 1;

    QSize removedSize = QSize(removedWidth ,removedHeight);

    QRect widgetRect = QRect(QPoint(x, y), correctSize);
    while (y < (d->gridSize.height() - removedSize.height()) && !found) {
        widgetRect.setY(y * (cellHeight + cellVMargin));
        widgetRect.setHeight(correctSize.height());
        while (x < d->gridSize.width() - removedSize.width() && !found) {
            bool intersects = false;
            widgetRect.setX(x * (cellWidth + cellHMargin));
            widgetRect.setWidth(correctSize.width());

            foreach(QRect draggerRect, widgetsRects) {
                if (widgetRect.intersects(draggerRect)) {
                    intersects = true;
                }
            }

            if (!intersects) {
                found = true;
            }
            x++;
        }
        x = 0;
        y++;
    }

    if (found) {
        return widgetRect;
    } else {
        return QRect(0, 0, 0, 0);
    }
}

void ViewManager::setLocked(bool locked)
{
    if (locked != d->locked) {
        d->locked = locked;
        emit lockedChanged(locked);
    }
}

void ViewManager::setViewWidth(int width)
{
    if (width != d->viewSize.width()) {
        d->viewSize.setWidth(width);
        d->recomputeGridCount();
    }
}

void ViewManager::setViewHeight(int height)
{
    if (height != d->viewSize.height()) {
        d->viewSize.setHeight(height);
        d->recomputeGridCount();
    }
}

void ViewManager::setCurrentPageIndex(int currentPageIndex)
{
    if (currentPageIndex != d->currentPageIndex) {
        d->currentPageIndex = currentPageIndex;
        emit currentPageIndexChanged(d->currentPageIndex);
    }
}

void ViewManager::setCurrentDraggedWidget(const QString &currentDraggedWidget)
{
    if (currentDraggedWidget != d->currentDraggedWidget) {
        d->currentDraggedWidget = currentDraggedWidget;
        emit currentDraggedWidgetChanged(d->currentDraggedWidget);
    }
}

void ViewManager::setHighlightRect(const QRect &highlightRect)
{
    if (highlightRect != d->highlightRect) {
        d->highlightRect = highlightRect;
        emit highlightRectChanged(d->highlightRect);
    }
}

void ViewManager::registerDragger(WidgetProperties * widget, QDeclarativeItem *item)
{
    d->registeredDraggers.insert(widget, item);
}

void ViewManager::unregisterDragger(WidgetProperties * widget)
{
    if (d->registeredDraggers.contains(widget)) {
        QDeclarativeItem *item = d->registeredDraggers.value(widget);
        d->registeredDraggers.remove(widget);
        item->deleteLater();
    }
}

void ViewManager::showWidgetSettings(Widgets::WidgetProperties * widget)
{
    emit requestShowWidgetSettings(widget->identifier());
}


}

#include "moc_viewmanager.cpp"
