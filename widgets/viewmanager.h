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
 * @file viewmanager.h
 * @short Definition of Widgets::ViewManager
 *
 * This file contains the definition of the
 * Widgets::ViewManager class.
 */

#ifndef WIDGETS_VIEWMANAGER_H
#define WIDGETS_VIEWMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include "widgetproperties.h"
#include "displayedpagesmodel.h"
#include "dockbaseproperties.h"

class QDeclarativeItem;
namespace Widgets
{

class SettingsWrapper;
/**
 * @short View manager
 *
 * This class is used to manage everything
 * that is related to the view. It is used
 * to control if the widgets are locked,
 * to create and destroy widget draggers as
 * well as compute the grid size and the
 * position of the highlighter.
 *
 * This class is used in QML context. Accessing
 * it is done using the "viewManager" global object.
 *
 * @section lock Locking widgets
 *
 * Locking widgets can be done from QML as well
 * as from C++. From QML it can be done
 * by modifying the locked property of
 * viewManager object. From C++, the methods
 * isLocked() and setLocked() should be used.
 *
 * @section grid Determining grid size
 *
 * Determining grid size is done by settings the
 * view width and height using setViewWidth() and
 * setViewHeight(). When these two parameters are set
 * the gridWidth() and gridHeight() properties are
 * available to determine the grid width and height.
 *
 * If the grid size is available, some other methods
 * like computeWidgetPosition() and
 * computeWidgetSize() can also be used in QML
 * view in order to fit the grid.
 *
 * @section drag Dragging widgets
 *
 * The view manager is also used for managing
 * widgets dragging. It is used to help creating
 * and managing a set of draggers that are used to
 * move widgets.
 *
 * ViewWidgetsDragManager is used to create
 * temporary WidgetDragger that covers each widget in
 * the current page and that are used to move the
 * widgets under them. In order to create these
 * items, the ViewWidgetsDragManager should know
 * the positions of each widget. This is done by providing
 * the position of the widgets, using the
 * requestCreateDragger() signal. This is done when
 * the widgets are unlocked.
 *
 * ViewWidgetsDragManager is connected to this signal
 * and creates the WidgetDragger that corresponds
 * to the currently displayed widgets.
 *
 * Once the draggers are created, they are also managed
 * by this class. This class then takes care of
 * destroying the draggers. It is done using
 * unregisterDragger(), that is used to destroy a
 * specific dragger. Note that all draggers are
 * destroyed when they are not needed anymore, when the
 * widgets are locked.
 *
 * In order to provide informations to delegate items
 * this class also provides global properties like
 * currentDraggedWidget() that is used in differend
 * QML items in order to manage the dragging.
 *
 * The highlightRect() property is also used to display
 * a highlight rectangle for the grid magnetism.
 *
 */
class ViewManager : public QObject
{
    Q_OBJECT
    /**
     * @short If the widgets are locked
     */
    Q_PROPERTY(bool locked READ isLocked WRITE setLocked NOTIFY lockedChanged)
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
    /**
     * @short Current page
     *
     * This property is used by this class to know
     * what is the current displayed page.
     */
    Q_PROPERTY(int currentPageIndex READ currentPageIndex WRITE setCurrentPageIndex
               NOTIFY currentPageIndexChanged)
    /**
     * @short Current dragged widget
     *
     * Current dragged widget, identified by
     * it's identifier.
     *
     * This property is used to relay the current
     * dragged widget to QML items.
     */
    Q_PROPERTY(QString currentDraggedWidget READ currentDraggedWidget WRITE setCurrentDraggedWidget
               NOTIFY currentDraggedWidgetChanged)
    /**
     * @short Highlight rectangle
     *
     * Geompetry of the highlight rectangle. Note that
     * the geometry is not changed is no widget is dragged
     * so the rectangle should be hidden if no widget
     * is currently dragged.
     */
    Q_PROPERTY(QRect highlightRect READ highlightRect WRITE setHighlightRect
               NOTIFY highlightRectChanged)
public:
    /**
     * @short Default constructor
     *
     * @param settingsWrapper SettingsWrapper object used provide settings.
     * @param displayedPagesModel DisplayedPagesModel object used to provide the models of the view.
     * @param parent parent object.
     */
    explicit ViewManager(SettingsWrapper *settingsWrapper = 0,
                         DisplayedPagesModel * displayedPagesModel = 0,
                         QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~ViewManager();
    /**
     * @short If the widgets are locked
     *
     * This method is used to retrieve if the
     * widgets are locked.
     *
     * @return if the widgets are locked.
     */
    bool isLocked() const;
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
    /**
     * @short Current page index
     *
     * This method is used to retrieve the
     * current page index.
     *
     * @return current page index.
     */
    int currentPageIndex() const;
    /**
     * @short Current dragged widget
     *
     * This method is used to retrieve the
     * widget that is currently being dragged,
     * identified, by it's identifier.
     *
     * @return current widget that is being dragged, identified by
     * it's identifier.
     */
    QString currentDraggedWidget() const;
    /**
     * @short Highlight rectangle
     *
     * This method is used to retrieve the
     * geometry of the highlight rectangle.
     *
     * @return the geometry of the highlight rectangle.
     */
    QRect highlightRect() const;

    /**
     * @short Compute widget position
     *
     * This method is used to compute the widget position
     * by taking the grid into account. It returns a position
     * that guarantee the widget to be in the grid.
     *
     * @param widgetX x coordiante of the widget.
     * @param widgetY y coordiante of the widget.
     * @return a point that is on the grid.
     */
    Q_INVOKABLE QPoint computeWidgetPosition(int widgetX, int widgetY) const;
    /**
     * @short Compute widget size
     *
     * This method is used to compute the widget size
     * by taking the grid into account. It returns a size
     * that guarantee the widget to be in the grid.
     *
     * @param widgetWidth width of the widget.
     * @param widgetHeight height of the widget.
     * @return a size that fits in the grid.
     */
    Q_INVOKABLE QSize computeWidgetSize(int widgetWidth, int widgetHeight) const;
    /**
     * @short Compute if there is a space available in the current page
     *
     * This method is used to compute if there is a space
     * that is available in the current page.
     *
     * If there is space, it returns a rectangle that
     * fits in the grid for the widget, and if there
     * is no space, it returns a rectangle of
     * size (0,0).
     *
     * @param widgetWidth width of the widget.
     * @param widgetHeight height of the widget.
     * @return a rectangle that fits in the grid.
     */
    Q_INVOKABLE QRect availableRect(int widgetWidth, int widgetHeight) const;
Q_SIGNALS:
    /**
     * @short Locked state changed
     *
     * Notify that the locked state
     * has changed.
     *
     * @param locked if the widgets are locked.
     */
    void lockedChanged(bool locked);
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
    /**
     * @short Current page index changed
     *
     * Notify that the current page index
     * has changed.
     *
     * @param currentPageIndex new page index.
     */
    void currentPageIndexChanged(int currentPageIndex);
    /**
     * @short Current dragged widget
     *
     * Notify that the current dragged widget,
     * identified by it's identifier, has
     * changed.
     *
     * @param currentDraggedWidget new dragged widget, identified
     * by it's identifier.
     */
    void currentDraggedWidgetChanged(const QString &currentDraggedWidget);
    /**
     * @short Highlight rectangle changed
     *
     * Notify that the highlight rectangle
     * has changed.
     *
     * @param highlightRect new highlight rectangle.
     */
    void highlightRectChanged(const QRect &highlightRect);
    /**
     * @short Request to create a dragger
     *
     * This signal is emitted when it is necessary
     * to create a dragger for a widget.
     *
     * @param widget widget for which the dragger should be created.
     */
    void requestCreateDragger(Widgets::WidgetProperties *widget);
    /**
     * @short Request to show widgets settings
     * 
     * This signal is emitted when it is necessary
     * for a widget to show it's settings.
     * 
     * @param identifier identifier that is used to identify the
     * widget.
     */
    void requestShowWidgetSettings(const QString &identifier);
public Q_SLOTS:
    /**
     * @short Set the locked state
     *
     * This method is used to set the locked
     * state of the widget.
     *
     * @param locked the locked state to set.
     */
    void setLocked(bool locked);
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
     * @short Set current page index
     *
     * This method is used to inform the ViewManager
     * that the current page index has changed.
     *
     * @param currentPageIndex new page index.
     */
    void setCurrentPageIndex(int currentPageIndex);
    /**
     * @short Set current dragger widget
     *
     * This method is used to inform the ViewManager
     * that the current dragged widget has changed.
     *
     * @param currentDraggedWidget new dragged widget,
     * identified by it's identifier.
     */
    void setCurrentDraggedWidget(const QString &currentDraggedWidget);
    /**
     * @short Set highlight rectangle
     *
     * This method is used to inform the ViewManager
     * that the highlight rectangle has changed.
     *
     * @param highlightRect new highlight rectangle.
     */
    void setHighlightRect(const QRect &highlightRect);
    /**
     * @short Register a dragger
     *
     * This method is used by ViewWidgetsDragManager
     * to register a dragger that is associated to
     * a widget.
     *
     * @param widget the widget which this dragger moves.
     * @param item the dragger item.
     */
    void registerDragger(Widgets::WidgetProperties * widget, QDeclarativeItem *item);
    /**
     * @short Unregister a dragger
     *
     * This method is used to unregister a dragger.
     * It will destroy the dragger that is associated
     * to a widget.
     *
     * @param widget the widget which the dragger should be destroyed.
     */
    void unregisterDragger(Widgets::WidgetProperties * widget);
    /**
     * @short Show widgets settings
     * 
     * This method is used to request a widget to
     * shows it's settings.
     * 
     * @param widget the widget which settings should be shown.
     */
    void showWidgetSettings(Widgets::WidgetProperties * widget);
private:
    class ViewManagerPrivate;
    /**
     * @short D-pointer
     */
    ViewManagerPrivate * const d;

    Q_PRIVATE_SLOT(d, void slotLockedChanged(bool locked))
    Q_PRIVATE_SLOT(d, void slotPageRowInserted(DisplayedPageWidgetsModel * page,
                                               const QModelIndex &parent, int start, int end))
};

}

#endif // WIDGETS_WIDGETSVIEWMANAGER_H
