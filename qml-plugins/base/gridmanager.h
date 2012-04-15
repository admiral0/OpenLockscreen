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

#ifndef WIDGETS_GRIDMANAGER_H
#define WIDGETS_GRIDMANAGER_H

#include <QtCore/QObject>

#include "settings.h"

namespace Widgets
{

class GridManagerPrivate;
class GridManager : public QObject
{
    Q_OBJECT
    /**
     * @short Grid cell width
     */
    Q_PROPERTY(int gridCellWidth READ gridCellWidth CONSTANT)
    /**
     * @short Grid cell height
     */
    Q_PROPERTY(int gridCellHeight READ gridCellHeight CONSTANT)
    /**
     * @short Grid cell horizontal margin
     */
    Q_PROPERTY(int gridCellHorizontalMargin READ gridCellHorizontalMargin CONSTANT)
    /**
     * @short Grid cell vertical margin
     */
    Q_PROPERTY(int gridCellVerticalMargin READ gridCellVerticalMargin CONSTANT)
    /**
     * @short Grid width
     *
     * The grid width is the number of columns in the grid.
     */
    Q_PROPERTY(int gridWidth READ gridWidth NOTIFY gridWidthChanged)
    /**
     * @short Grid height
     *
     * The grid width is the number of rows in the grid.
     */
    Q_PROPERTY(int gridHeight READ gridHeight NOTIFY gridHeightChanged)
    Q_PROPERTY(Widgets::Settings * settings READ settings WRITE setSettings NOTIFY settingsChanged)
public:
    explicit GridManager(QObject *parent = 0);
    virtual ~GridManager();
    /**
     * @short Grid cell width
     *
     * This method is used to retrieve
     * the value of "view/gridCellWidth" settings.
     *
     * @return the grid cell width settings.
     */
    int gridCellWidth() const;
    /**
     * @short Grid cell height
     *
     * This method is used to retrieve
     * the value of "view/gridCellHeight" settings.
     *
     * @return the grid cell height settings.
     */
    int gridCellHeight() const;
    /**
     * @short Grid cell horizontal margin
     *
     * This method is used to retrieve
     * the value of "view/gridCellHorizontalMargin" settings.
     *
     * @return the grid cell horizontal margin.
     */
    int gridCellHorizontalMargin() const;
     /**
     * @short Grid cell vertical margin
     *
     * This method is used to retrieve
     * the value of "view/gridCellVerticalMargin" settings.
     *
     * @return the grid cell vertical margin.
     */
    int gridCellVerticalMargin() const;
    /**
     * @short Grid width
     *
     * This method is used to retrieve the
     * width of the grid (number of columns).
     *
     * @return width of the grid.
     */
    int gridWidth() const;
    /**
     * @short Grid height
     *
     * This method is used to retrieve the
     * height of the grid (number of rows).
     *
     * @return height of the grid.
     */
    int gridHeight() const;
    Settings * settings() const;
Q_SIGNALS:
    void gridCellWidthChanged(int gridCellWidth);
    void gridCellHeightChanged(int gridCellHeight);
    void gridCellHorizontalMarginChanged(int gridCellHorizontalMargin);
    void gridCellVerticalMarginChanged(int gridCellVerticalMargin);
    /**
     * @short Grid width changed
     *
     * Notify that the grid width
     * has changed.
     *
     * @param gridWidth new grid width.
     */
    void gridWidthChanged(int gridWidth);
    /**
     * @short Grid height changed
     *
     * Notify that the grid height
     * has changed.
     *
     * @param gridHeight new grid height.
     */
    void gridHeightChanged(int gridHeight);
    void settingsChanged();
public Q_SLOTS:
    /**
     * @short Set view width
     *
     * This method is used to inform the ViewManager
     * that the view width has changed, in order
     * to recompute the grid size.
     *
     * @param width new view width.
     */
    void setViewWidth(int width);
    /**
     * @short Set view height
     *
     * This method is used to inform the ViewManager
     * that the view height has changed, in order
     * to recompute the grid size.
     *
     * @param height new view height.
     */
    void setViewHeight(int height);

    void setSettings(Settings *settings);
protected:
    const QScopedPointer<GridManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(GridManager)
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(const QString &key, const QVariant &value))
};

}

#endif // WIDGETS_GRIDMANAGER_H
