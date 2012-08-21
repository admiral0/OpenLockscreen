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

/**
 * @file gridmanager.h
 * @short Definition of Widgets::GridManager
 */

#include <QtCore/QObject>
#include <QtCore/QRect>

#include "settings.h"

namespace Widgets
{

class GridManagerPrivate;
/**
 * @brief Grid manager
 *
 * This class is used to provide a grid that should
 * be displayed over a graphical component. It takes the
 * size of the graphical component, that is called the "view",
 * in account, as well some settings, including the size of a cell
 * and margins between cells, and then, computes a grid and a
 * container size, that is the biggest space that can be fit with
 * the provided grid, and that is lesser than the size of the view.
 *
 * It also provides methods to fit a component in the grid. A
 * component is fit in the grid if the edges of the components
 * are also edges of cells.
 *
 * This component is mostly manipulated through a QML context, so
 * many of the settings, and computed results are available as
 * properties. An important property is settings, that provides a
 * Widgets::Settings class to the grid manager, in which it can
 * retrieve settings related to the grid.
 *
 * The grid is recomputed each time settings are changed, or if the
 * size of the view has changed.
 *
 * Important properties are
 * - gridWidth(), that is the number of columns in the grid.
 * - gridHeight(), that is the number of rows in the grid.
 * - containerWidth(), that is the available width for the grid.
 * - containerHeight(), that is the available height for the grid.
 *
 * Important methods are
 * - fitPosition()
 * - fitSize()
 * - fit()
 *
 * The first method is used to fit a position, in order to set the
 * given position to the closest grid point. The second method is used
 * to fit a size, it returns the minimum size that is greater than the
 * provided size, in order to fit in the grid. The last method do both,
 * it fits the position and the size.
 *
 * Remark, the settings property refers to the pointer to the Widgets::Settings
 * object. settingsChanged() is emitted when this pointer changed. When
 * settings related to grid size or margins changed, specific signals are
 * emitted.
 */
class GridManager : public QObject
{
    Q_OBJECT
    /**
     * @short Grid cell width
     */
    Q_PROPERTY(int gridCellWidth READ gridCellWidth NOTIFY gridCellWidthChanged)
    /**
     * @short Grid cell height
     */
    Q_PROPERTY(int gridCellHeight READ gridCellHeight NOTIFY gridCellHeightChanged)
    /**
     * @short Grid cell horizontal margin
     */
    Q_PROPERTY(int gridCellHorizontalMargin READ gridCellHorizontalMargin
               NOTIFY gridCellHorizontalMarginChanged)
    /**
     * @short Grid cell vertical margin
     */
    Q_PROPERTY(int gridCellVerticalMargin READ gridCellVerticalMargin
               NOTIFY gridCellVerticalMarginChanged)
    /**
     * @short Grid width
     */
    Q_PROPERTY(int gridWidth READ gridWidth NOTIFY gridWidthChanged)
    /**
     * @short Grid height
     */
    Q_PROPERTY(int gridHeight READ gridHeight NOTIFY gridHeightChanged)
    /**
     * @short Container width
     */
    Q_PROPERTY(int containerWidth READ containerWidth NOTIFY containerWidthChanged)
    /**
     * @short Container height
     */
    Q_PROPERTY(int containerHeight READ containerHeight NOTIFY containerHeightChanged)
    /**
     * @short Settings
     */
    Q_PROPERTY(Widgets::Settings * settings READ settings WRITE setSettings NOTIFY settingsChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit GridManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~GridManager();
    /**
     * @short Grid cell width
     * @return the grid cell width.
     */
    int gridCellWidth() const;
    /**
     * @short Grid cell height
     * @return the grid cell height.
     */
    int gridCellHeight() const;
    /**
     * @short Grid cell horizontal margin
     * @return the grid cell horizontal margin.
     */
    int gridCellHorizontalMargin() const;
     /**
     * @short Grid cell vertical margin
     * @return the grid cell vertical margin.
     */
    int gridCellVerticalMargin() const;
    /**
     * @short Grid width
     * @return the grid width.
     */
    int gridWidth() const;
    /**
     * @short Grid height
     * @return the grid height.
     */
    int gridHeight() const;
    /**
     * @brief Container width
     * @return the container width.
     */
    int containerWidth() const;
    /**
     * @brief The container height
     * @return the container height.
     */
    int containerHeight() const;
    /**
     * @brief Settings
     * @return settings.
     */
    Settings * settings() const;
    /**
     * @brief Fit a geometry
     *
     * This method is used to fit a geometry, that
     * is both a position and a size. It uses fitPosition()
     * and fitSize().
     *
     * @param geometry the geometry to fit.
     * @return a fitted geometry.
     */
    QRect fit(const QRect &geometry) const;
    /**
     * @brief Fit a position
     *
     * This method is used to fit a position. The fitted position
     * will always be the closest point that is on the top-left
     * corner of a cell.
     *
     * @param position the position to fit.
     * @return a fitted position.
     */
    QPoint fitPosition(const QPoint &position) const;
    /**
     * @brief Fit a size
     *
     * This method is used to fit a size. The fitted size
     * will always be bigger than the provided size, but will
     * be the size that covers the smallest amount of cells.
     *
     * @param size the size to fit.
     * @return a fitted size.
     */
    QSize fitSize(const QSize &size) const;
Q_SIGNALS:
    /**
     * @brief Grid cell width changed
     */
    void gridCellWidthChanged();
    /**
     * @brief Grid cell height changed
     */
    void gridCellHeightChanged();
    /**
     * @brief Grid cell horizontal margins changed
     */
    void gridCellHorizontalMarginChanged();
    /**
     * @brief Grid cell vertical margins changed
     */
    void gridCellVerticalMarginChanged();
    /**
     * @short Grid width changed
     */
    void gridWidthChanged();
    /**
     * @short Grid height changed
     */
    void gridHeightChanged();
    /**
     * @brief Container width changed
     */
    void containerWidthChanged();
    /**
     * @brief Container height changed
     */
    void containerHeightChanged();
    /**
     * @brief Settings changed
     */
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
    /**
     * @brief Set settings
     * @param settings the settings to set.
     */
    void setSettings(Settings *settings);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    GridManager(GridManagerPrivate * dd, QObject *parent = 0);
    /**
     * @brief D-pointer
     */
    const QScopedPointer<GridManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(GridManager)
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(const QString &group, const QString &key,
                                                   const QVariant &value))
};

}

#endif // WIDGETS_GRIDMANAGER_H
