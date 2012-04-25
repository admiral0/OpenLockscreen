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

#include "gridmanager.h"

#include <QtCore/QDebug>
#include <QtCore/QSize>

#include "settings.h"

static const char *GRID_GROUP = "grid";
static const char *GRID_CELL_WIDTH_KEY = "cellWidth";
static const char *GRID_CELL_HEIGHT_KEY = "cellHeight";
static const char *GRID_CELL_HMARGIN_KEY = "cellHorizontalMargin";
static const char *GRID_CELL_VMARGIN_KEY = "cellVerticalMargin";

namespace Widgets
{

class GridManagerPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param settingsWrapper SettingsWrapper object used provide settings.
     * @param q Q-pointer.
     */
    GridManagerPrivate(GridManager *q);
    /**
     * @short Recompute the grid count
     *
     * This method is used to recompute the grid count.
     * It should be called if the view size has changed
     * or if the grid cell parameters has changed.
     */
    void recomputeGridCount();
    void loadSettings();
    void slotValueChanged(const QString &group, const QString &key, const QVariant &value);
    /**
     * @short View size
     */
    QSize viewSize;
    QSize gridCellSize;
    QSize gridCellMarginsSize;
    /**
     * @short Grid size
     */
    QSize gridSize;
    /**
     * @short %Settings
     */
    Settings * settings;
private:
    Q_DECLARE_PUBLIC(GridManager)
    /**
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
        emit q->gridWidthChanged(newGridWidth);
        emit q->containerWidthChanged(q->containerWidth());
    }

    if (newGridHeight != gridSize.height()) {
        gridSize.setHeight(newGridHeight );
        emit q->gridHeightChanged(newGridHeight);
        emit q->containerHeightChanged(q->containerHeight());
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
    if (group != GRID_GROUP) {
        return;
    }

    if(key == GRID_CELL_WIDTH_KEY) {
        gridCellSize.setWidth(value.toInt());
        recomputeGridCount();
    } else if(key == GRID_CELL_HEIGHT_KEY) {
        gridCellSize.setHeight(value.toInt());
        recomputeGridCount();
    } else if(key == GRID_CELL_HMARGIN_KEY) {
        gridCellMarginsSize.setWidth(value.toInt());
        recomputeGridCount();
    } else if(key == GRID_CELL_VMARGIN_KEY) {
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

int GridManager::containerWidth() const
{
    Q_D(const GridManager);
    int cellAndMargin = d->gridCellSize.width() + d->gridCellMarginsSize.width();
    return cellAndMargin * d->gridSize.width() - d->gridCellMarginsSize.width();
}

int GridManager::gridHeight() const
{
    Q_D(const GridManager);
    return d->gridSize.height();
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
