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

#include <QtCore/QSize>
#include <QtCore/QDebug>

#include "settings.h"

static const char *GRID_CELL_WIDTH_KEY = "view/gridCellWidth";
static const char *GRID_CELL_HEIGHT_KEY = "view/gridCellHeight";
static const char *GRID_CELL_HMARGIN_KEY = "view/gridCellHorizontalMargin";
static const char *GRID_CELL_VMARGIN_KEY = "view/gridCellVerticalMargin";

namespace Widgets
{

class GridManager::GridManagerPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param settingsWrapper SettingsWrapper object used provide settings.
     * @param parent parent Q-pointer.
     */
    GridManagerPrivate(GridManager *parent);
    /**
     * @short Recompute the grid count
     *
     * This method is used to recompute the grid count.
     * It should be called if the view size has changed
     * or if the grid cell parameters has changed.
     */
    void recomputeGridCount();
    void loadSettings();
    void slotValueChanged(const QString &key, const QVariant &value);
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
    /**
     * @short Q-pointer
     */
    GridManager * const q;
};

GridManager::GridManagerPrivate::GridManagerPrivate(GridManager *parent):
    q(parent)
{
    viewSize = QSize(0, 0);
    gridCellSize = QSize(0, 0);
    gridCellMarginsSize = QSize(0, 0);
    gridSize = QSize(0, 0);
    settings = 0;
}

void GridManager::GridManagerPrivate::recomputeGridCount()
{
    int cellWidth = gridCellSize.width();
    int cellHeight = gridCellSize.height();
    int cellHMargin = gridCellMarginsSize.width();
    int cellVMargin = gridCellMarginsSize.height();

    if(cellWidth == 0 || cellHeight == 0) {
        return;
    }

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

void GridManager::GridManagerPrivate::loadSettings()
{
    int cellWidth = settings->value(GRID_CELL_WIDTH_KEY).toInt();
    int cellHeight = settings->value(GRID_CELL_HEIGHT_KEY).toInt();
    int cellHMargin = settings->value(GRID_CELL_HMARGIN_KEY).toInt();
    int cellVMargin = settings->value(GRID_CELL_VMARGIN_KEY).toInt();

    gridCellSize.setWidth(cellWidth);
    gridCellSize.setHeight(cellHeight);

    gridCellMarginsSize.setWidth(cellHMargin);
    gridCellMarginsSize.setHeight(cellVMargin);

    recomputeGridCount();
}

void GridManager::GridManagerPrivate::slotValueChanged(const QString &key, const QVariant &value)
{
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
    QObject(parent), d(new GridManagerPrivate(this))
{
}

GridManager::~GridManager()
{
    delete d;
}

int GridManager::gridCellWidth() const
{
    return d->gridCellSize.width();
}

int GridManager::gridCellHeight() const
{
    return d->gridCellSize.height();
}

int GridManager::gridWidth() const
{
    return d->gridSize.width();
}

int GridManager::gridHeight() const
{
    return d->gridSize.height();
}

Settings * GridManager::settings() const
{
    return d->settings;
}

void GridManager::setViewWidth(int width)
{
    if (d->viewSize.width() != width) {
        d->viewSize.setWidth(width);
        d->recomputeGridCount();
    }
}

void GridManager::setViewHeight(int height)
{
    if (d->viewSize.height() != height) {
        d->viewSize.setHeight(height);
        d->recomputeGridCount();
    }
}

void GridManager::setSettings(Settings *settings)
{
    if(d->settings == 0) {
        d->settings = settings;
        d->loadSettings();
        connect(d->settings, SIGNAL(valueChanged(QString,QVariant)),
                this, SLOT(slotValueChanged(QString,QVariant)));

        emit settingsChanged();
    }
}

}

#include "moc_gridmanager.cpp"
