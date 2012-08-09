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
 * @file gridmanager.cpp
 * @short Implementation of Widgets::GridManager
 */

#include "gridmanager.h"

#include <QtCore/QDebug>
#include <QtCore/QSize>
#include <QtCore/qmath.h>

#include "settings.h"

/**
 * @brief GRID_GROUP
 *
 * Used in Widgets::GridManager.
 */
static const char *GRID_GROUP = "grid";
/**
 * @brief GRID_CELL_WIDTH_KEY
 *
 * Used in Widgets::GridManager.
 */
static const char *GRID_CELL_WIDTH_KEY = "cellWidth";
/**
 * @brief GRID_CELL_HEIGHT_KEY
 *
 * Used in Widgets::GridManager.
 */
static const char *GRID_CELL_HEIGHT_KEY = "cellHeight";
/**
 * @brief GRID_CELL_HMARGIN_KEY
 *
 * Used in Widgets::GridManager.
 */
static const char *GRID_CELL_HMARGIN_KEY = "cellHorizontalMargin";
/**
 * @brief GRID_CELL_VMARGIN_KEY
 *
 * Used in Widgets::GridManager.
 */
static const char *GRID_CELL_VMARGIN_KEY = "cellVerticalMargin";

namespace Widgets
{

/**
 * @internal
 * @brief Private class for GridManager
 */
class GridManagerPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    GridManagerPrivate(GridManager *q);
    /**
     * @internal
     * @short Recompute the grid count
     *
     * This method is used to recompute the grid count.
     * It should be called if the view size has changed
     * or if the grid cell parameters has changed.
     */
    void recomputeGridCount();
    /**
     * @internal
     * @brief Load settings
     *
     * This method is used to load settings from the
     * settings object.
     *
     * It triggers a grid recompute.
     */
    void loadSettings();
    /**
     * @internal
     * @brief Slot value changed
     *
     * This slot is used to react from change of settings.
     * It triggers a grid recompute.
     *
     * @param group settings group.
     * @param key settings key.
     * @param value settings value.
     */
    void slotValueChanged(const QString &group, const QString &key, const QVariant &value);
    /**
     * @internal
     * @short View size
     */
    QSize viewSize;
    /**
     * @internal
     * @brief Grid cell size
     */
    QSize gridCellSize;
    /**
     * @internal
     * @brief Grid margins size
     */
    QSize gridCellMarginsSize;
    /**
     * @internal
     * @short Grid size
     */
    QSize gridSize;
    /**
     * @internal
     * @short %Settings
     */
    Settings * settings;
private:
    Q_DECLARE_PUBLIC(GridManager)
    /**
     * @internal
     * @short Q-pointer
     */
    GridManager * const q_ptr;
};

GridManagerPrivate::GridManagerPrivate(GridManager *q):
    q_ptr(q)
{
    viewSize = QSize(0, 0);
    gridCellSize = QSize(0, 0);
    gridCellMarginsSize = QSize(0, 0);
    gridSize = QSize(0, 0);
    settings = 0;
}

void GridManagerPrivate::recomputeGridCount()
{
    Q_Q(GridManager);
    int cellWidth = gridCellSize.width();
    int cellHeight = gridCellSize.height();
    int cellHMargin = gridCellMarginsSize.width();
    int cellVMargin = gridCellMarginsSize.height();

    if(cellWidth == 0 || cellHeight == 0) {
        gridSize = QSize(0, 0);
        return;
    }

    if (viewSize.width() <= 0 || viewSize.height() <= 0) {
        gridSize = QSize(0, 0);
        return;
    }

    int newGridWidth = (viewSize.width() + cellHMargin) / (cellWidth + cellHMargin);
    int newGridHeight = (viewSize.height() + cellVMargin) / (cellHeight + cellVMargin);


    if (newGridWidth != gridSize.width()) {
        gridSize.setWidth(newGridWidth);
        emit q->gridWidthChanged();
        emit q->containerWidthChanged();
    }

    if (newGridHeight != gridSize.height()) {
        gridSize.setHeight(newGridHeight );
        emit q->gridHeightChanged();
        emit q->containerHeightChanged();
    }
}

void GridManagerPrivate::loadSettings()
{
    int cellWidth = settings->value(GRID_GROUP, GRID_CELL_WIDTH_KEY).toInt();
    int cellHeight = settings->value(GRID_GROUP, GRID_CELL_HEIGHT_KEY).toInt();
    int cellHMargin = settings->value(GRID_GROUP, GRID_CELL_HMARGIN_KEY).toInt();
    int cellVMargin = settings->value(GRID_GROUP, GRID_CELL_VMARGIN_KEY).toInt();

    gridCellSize.setWidth(cellWidth);
    gridCellSize.setHeight(cellHeight);

    gridCellMarginsSize.setWidth(cellHMargin);
    gridCellMarginsSize.setHeight(cellVMargin);

    recomputeGridCount();
}

void GridManagerPrivate::slotValueChanged(const QString &group, const QString &key,
                                          const QVariant &value)
{
    Q_Q(GridManager);
    if (group != GRID_GROUP) {
        return;
    }

    if(key == GRID_CELL_WIDTH_KEY) {
        gridCellSize.setWidth(value.toInt());
        emit q->gridCellWidthChanged();
        recomputeGridCount();
    } else if(key == GRID_CELL_HEIGHT_KEY) {
        emit q->gridCellHeightChanged();
        gridCellSize.setHeight(value.toInt());
        recomputeGridCount();
    } else if(key == GRID_CELL_HMARGIN_KEY) {
        emit q->gridCellHorizontalMarginChanged();
        gridCellMarginsSize.setWidth(value.toInt());
        recomputeGridCount();
    } else if(key == GRID_CELL_VMARGIN_KEY) {
        emit q->gridCellVerticalMarginChanged();
        gridCellMarginsSize.setHeight(value.toInt());
        recomputeGridCount();
    }
}

////// End of private class //////

GridManager::GridManager(QObject *parent):
    QObject(parent), d_ptr(new GridManagerPrivate(this))
{
}

GridManager::GridManager(GridManagerPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

GridManager::~GridManager()
{
}

int GridManager::gridCellWidth() const
{
    Q_D(const GridManager);
    return d->gridCellSize.width();
}

int GridManager::gridCellHeight() const
{
    Q_D(const GridManager);
    return d->gridCellSize.height();
}

int GridManager::gridCellHorizontalMargin() const
{
    Q_D(const GridManager);
    return d->gridCellMarginsSize.width();
}

int GridManager::gridCellVerticalMargin() const
{
    Q_D(const GridManager);
    return d->gridCellMarginsSize.height();
}

int GridManager::gridWidth() const
{
    Q_D(const GridManager);
    return d->gridSize.width();
}

int GridManager::gridHeight() const
{
    Q_D(const GridManager);
    return d->gridSize.height();
}

int GridManager::containerWidth() const
{
    Q_D(const GridManager);
    int cellAndMargin = d->gridCellSize.width() + d->gridCellMarginsSize.width();
    return cellAndMargin * d->gridSize.width() - d->gridCellMarginsSize.width();
}

int GridManager::containerHeight() const
{
    Q_D(const GridManager);
    int cellAndMargin = d->gridCellSize.height() + d->gridCellMarginsSize.height();
    return cellAndMargin * d->gridSize.height() - d->gridCellMarginsSize.height();
}

Settings * GridManager::settings() const
{
    Q_D(const GridManager);
    return d->settings;
}

QRect GridManager::fit(const QRect &geometry) const
{
    return QRect(fitPosition(geometry.topLeft()), fitSize(geometry.size()));
}

QPoint GridManager::fitPosition(const QPoint &position) const
{
    Q_D(const GridManager);
    int cellWidth = d->gridCellSize.width();
    int cellHeight = d->gridCellSize.height();
    int cellHMargin = d->gridCellMarginsSize.width();
    int cellVMargin = d->gridCellMarginsSize.height();
    int oldX = position.x();
    int oldY = position.y();

    float xRatio = (float) (oldX + cellHMargin) / (cellWidth + cellHMargin);
    int x = qRound(xRatio) * (cellWidth + cellHMargin);

    float yRatio = (float) (oldY + cellVMargin) / (cellHeight + cellVMargin);
    int y = qRound(yRatio) * (cellHeight + cellVMargin);

    return QPoint(x, y);
}

QSize GridManager::fitSize(const QSize &size) const
{
    Q_D(const GridManager);
    int cellWidth = d->gridCellSize.width();
    int cellHeight = d->gridCellSize.height();
    int cellHMargin = d->gridCellMarginsSize.width();
    int cellVMargin = d->gridCellMarginsSize.height();
    int oldWidth = size.width();
    int oldHeight = size.height();

    float rowCount = ((float) oldWidth + (float) cellHMargin) /
                     ((float) cellWidth + (float) cellHMargin);
    float columnCount = ((float) oldHeight + (float) cellVMargin) /
                        ((float) cellHeight + (float) cellVMargin);

    int width = qCeil(rowCount) * cellWidth + qMax(0, qCeil(rowCount - 1)) * cellHMargin - 1;
    int height = qCeil(columnCount) * cellHeight + qMax(0, qCeil(columnCount - 1)) * cellVMargin;

    return QSize(width, height);
}

void GridManager::setViewWidth(int width)
{
    Q_D(GridManager);
    if (d->viewSize.width() != width) {
        d->viewSize.setWidth(width);
        d->recomputeGridCount();
    }
}

void GridManager::setViewHeight(int height)
{
    Q_D(GridManager);
    if (d->viewSize.height() != height) {
        d->viewSize.setHeight(height);
        d->recomputeGridCount();
    }
}

void GridManager::setSettings(Settings *settings)
{
    Q_D(GridManager);
    if(settings == 0) {
        return;
    }

    if(d->settings == 0) {
        d->settings = settings;
        d->loadSettings();
        connect(d->settings, SIGNAL(valueChanged(QString,QString,QVariant)),
                this, SLOT(slotValueChanged(QString,QString,QVariant)));

        emit settingsChanged();
    }
}

}

#include "moc_gridmanager.cpp"
