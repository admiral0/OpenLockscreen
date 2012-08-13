/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef WIDGETS_DRAG_DRAGMANAGER_H
#define WIDGETS_DRAG_DRAGMANAGER_H

/**
 * @file dragmanager.h
 * @short Definition of Widgets::Drag::DragManager
 */

#include <QtCore/QObject>
#include "widgetproperties.h"
#include "gridmanager.h"

class QDeclarativeContext;
class QDeclarativeItem;
namespace Widgets
{

class WidgetsPageListModel;
namespace Drag
{

class DragManagerPrivate;
/**
 * @brief The drag manager
 *
 * The drag manager is a conveinent QML interface
 * to manage components that are used for
 * dragging widgets.
 *
 * The dragging process is a bit complicated
 * since draggers are invisible overlays that
 * are drawn over widgets, and that can be
 * dragged. While a dragger is clicked and
 * dragged, the dragger become visible, and
 * the widget is hidden.
 *
 * This class is responsible of providing
 * information about the state of the view,
 * if it is locked, or busy. While locked,
 * the draggers shouldn't exist, and while
 * locked, the draggers should be disabled.
 *
 * It is also used to request the creating
 * of draggers while the widgets are unlocked,
 * or when another page is shown.
 *
 * Finally, it is also responsible of setting the
 * properties of the widget when the drag is
 * finished.
 *
 * This class use a grid manager to
 * be able to take the grid in account.
 */
class DragManager : public QObject
{
    Q_OBJECT
    /**
     * @short If the view is busy
     */
    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)
    /**
     * @short If the view is locked
     */
    Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged)
    /**
     * @short Grid manager
     */
    Q_PROPERTY(Widgets::GridManager *gridManager READ gridManager WRITE setGridManager
               NOTIFY gridManagerChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit DragManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DragManager();
    /**
     * @brief Set the widgets page list model
     *
     * This method is called to set the current widgets page list model.
     * It should not be called from a QML context, but be called
     * when the plugin is loaded, to set the provider to the global
     * provider.
     *
     * @param widgetsPageListModel
     */
    void setWidgetsPageListModel(WidgetsPageListModel *widgetsPageListModel);
    /**
     * @brief If the view is busy
     * @return if the view is busy.
     */
    bool busy() const;
    /**
     * @brief If the view is locked
     * @return if the view is locked.
     */
    bool locked() const;
    /**
     * @brief Grid manager
     * @return grid manager
     */
    GridManager * gridManager() const;
Q_SIGNALS:
    /**
     * @brief The view's busy state changed
     */
    void busyChanged();
    /**
     * @brief The view's locked state changed
     */
    void lockedChanged();
    /**
     * @brief Grid manager changed
     */
    void gridManagerChanged();
    /**
     * @brief Ask to disable all draggers
     *
     * This signal is sent when all draggers should
     * be disabled, but not removed yet. For example,
     * when the current page changed, this request is
     * sent.
     */
    void requestDisableDraggers();
    /**
     * @brief Ask to create (or enable) a dragger
     *
     * This signal is send when a dragger should be
     * created, or enabled. For example, when the widgets
     * are unlocked, this request is sent for every
     * widget in the current page.
     *
     * @param widgetProperties properties of the widget associated to the dragger to create.
     */
    void requestCreateDragger(Widgets::WidgetProperties *widgetProperties);
    /**
     * @brief Ask to delete all draggers
     *
     * This signal is sent when all draggers should be
     * deleted. For example, when the widgets are locked,
     * this request is sent.
     */
    void requestDeleteDraggers();
    /**
     * @brief The widget is dragged
     *
     * This signal is send when a widget is being dragged, using
     * the method drag(). It is only emitted when the position of
     * the widget changed on the grid.
     *
     * @param widgetProperties properties of the widget being dragged.
     * @param rect the new position of the widget.
     */
    void widgetDragged(Widgets::WidgetProperties *widgetProperties, const QRect &rect);
public Q_SLOTS:
    /**
     * @brief Set the view's busy state
     * @param busy if the view is busy.
     */
    void setBusy(bool busy);
    /**
     * @brief Set the view's locked state
     * @param locked if the view is locked.
     */
    void setLocked(bool locked);
    /**
     * @brief Set the grid manager
     * @param gridManager the grid manager.
     */
    void setGridManager(Widgets::GridManager *gridManager);
    /**
     * @brief Drag a widget
     *
     * This method should be called when a widget is being dragged.
     * It is used to compute the position of the widget on the grid.
     * It also hides the widget, and shows the dragger.
     *
     * When the widget's position on the grid has changed, widgetDragged()
     * is emitted.
     *
     * When the drag is finished, finishDrag() should be called.
     *
     * @param widgetProperties properties of the widget being dragged.
     * @param rect the current geometry of the widget being dragged.
     */
    void drag(Widgets::WidgetProperties *widgetProperties, const QRect &rect);
    /**
     * @brief Finish a drag
     *
     * This method is used to finish a drag. It is used to update the
     * position of the widget, and send it to the widget list model.
     * It is also used to hide the dragger and show the widget.
     *
     * @param widgetProperties properties of the widget being dragged.
     * @param dragger the dragger used for the widget.
     * @param rect the current geometry of the widget being dragged.
     */
    void finishDrag(Widgets::WidgetProperties *widgetProperties, QDeclarativeItem *dragger,
                    const QRect &rect);
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<DragManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DragManager)
    /// \cond buggy-doxygen-doc
    Q_PRIVATE_SLOT(d_func(), void createDraggers())
    Q_PRIVATE_SLOT(d_func(), void establishPageConnection())
    /// \endcond
};

}

}

#endif // WIDGETS_DRAG_DRAGMANAGER_H
