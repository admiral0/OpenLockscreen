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

#ifndef WIDGETS_DRAG_PLUGIN_H
#define WIDGETS_DRAG_PLUGIN_H

/**
 * @file widgets_drag_plugin.h
 * @short Definition of Widgets::Drag::WidgetsDragPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>

/**
 * \page pluginDrag QML plugins for drag management
 *
 * This plugin extends libwidgets by bringing the ability to move
 * widgets on the screen and relayout them.
 *
 * In order to use this plugin, you have to import the following plugin
 * @code{.qml}
 * import org.SfietKonstantin.widgets.drag 1.0
 * @endcode
 *
 * While imported, this plugin provides a drag manager, that provides
 * an interface for managing draggers, that are an overlay component that
 * is used to move the widget.
 *
 * A dragger is simply some clickable and movable component, that draws a
 * copy of the widget. While it is clicked, it hides the widget it should
 * manage and shows the copy. Only the dragger is moved, and the widget is
 * moved only when the dragger is released.
 *
 * Implementing drag management is harder than using widgets or docks, but
 * a drag overlay is already implemented. It is the \em DragOverlay
 * component.
 *
 * @see Widgets::Drag::DragManager
 */

namespace Widgets
{
/**
 * @short Namespace for drag management
 */
namespace Drag
{

/**
 * @internal
 * @short QML plugin for drag management
 */
class WidgetsDragPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    /**
     * @internal
     * @brief Initialize engine
     * @param engine QML engine.
     * @param uri uri used in the import.
     */
    virtual void initializeEngine(QDeclarativeEngine *engine, const char *uri);
    /**
     * @internal
     * @short Register types
     * @param uri uri used in the import.
     */
    virtual void registerTypes(const char *uri);
};

}

}

#endif // WIDGETS_DRAG_PLUGIN_H

