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

#ifndef WIDGETS_DRAG_DRAGGERMANAGER_H
#define WIDGETS_DRAG_DRAGGERMANAGER_H

/**
 * @file draggermanager.h
 * @short Definition of Widgets::Drag::DraggerManager
 */

#include <QtCore/QObject>

class QDeclarativeItem;
namespace Widgets
{

class WidgetProperties;
namespace Drag
{

class DraggerManagerPrivate;

/**
 * @brief Dragger manager
 *
 * This class is used to manage the created draggers.
 * Since draggers should be created, shown or deleted
 * following orders of the drag manager, this class is
 * used to perform these task in a better way.
 *
 * While created in a QML context, draggers should be
 * manipulated with this class using
 * - registerDragger()
 * - unregisterDragger()
 * - unregisterDraggers()
 * - disableDraggers()
 *
 * The first method is used to associate a created dragger
 * wht the corresponding widget. The second and third methods
 * are used to remove draggers, and the last one is used
 * to disable them, hiding them.
 *
 * While trying to register widgets, it can be interesting
 * to call draggerExists() to check if the dragger is not
 * already registered.
 */
class DraggerManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit DraggerManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DraggerManager();
    /**
     * @short If a dragger exists
     * @param widgetProperties properties of the widget that the dragger controls.
     * @return if a dragger associated to the provided widget exits.
     */
    Q_INVOKABLE bool draggerExists(Widgets::WidgetProperties *widgetProperties);
public Q_SLOTS:
    /**
     * @brief Register a dragger
     * @param widgetProperties properties of the widget that the dragger controls.
     * @param dragger the dragger to register.
     */
    void registerDragger(Widgets::WidgetProperties *widgetProperties, QDeclarativeItem *dragger);
    /**
     * @brief Unregister a dragger
     * @param widgetProperties properties of the widget for which
     *        the dragger should be unregistered.
     */
    void unregisterDragger(Widgets::WidgetProperties *widgetProperties);
    /**
     * @brief Unregister all the draggers
     */
    void unregisterDraggers();
    /**
     * @brief Disable all the draggers
     */
    void disableDraggers();
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<DraggerManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DraggerManager)
};

}

}

#endif // WIDGETS_DRAG_DRAGGERMANAGER_H
