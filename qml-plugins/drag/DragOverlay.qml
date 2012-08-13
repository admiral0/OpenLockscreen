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

import QtQuick 1.1
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.drag 1.0
//import com.nokia.meego 1.0
//import "UiConstants.js" as UI

// Drag overlay
// This component creates widget
// draggers that are used to move
// the different widgets

Item {
    id: container
    property Item widgetsView

    signal showWidgetSettings(variant widget)
    anchors.fill: widgetsView

    DraggerManager {
        id: draggerManager
    }

    Connections {
        target: widgetsView
        onBusyChanged: DragManagerInstance.busy = widgetsView.busy
    }

    Item {
        id: contentsContainer
        parent: widgetsView.contentItem
        anchors.fill: parent

        Rectangle {
            id: highlighter

            Connections {
                target: DragManagerInstance
                onWidgetDragged: {
                    highlighter.x = rect.x
                    highlighter.y = rect.y
                    highlighter.width = rect.width
                    highlighter.height = rect.height
                }
            }
        }
    }

    // Create a dragger
    function createDragger(widget) {
        var qmlFile = ProviderManagerInstance.provider.widgetFile(widget.fileName,
                                                                  widget.disambiguation)
        var component = Qt.createComponent("WidgetDragger.qml")
        if (component.status == Component.Ready) {
            var dragger = component.createObject(contentsContainer,
                                                 {"widget": widget,
                                                  "qmlFile": qmlFile});
            draggerManager.registerDragger(widget, dragger)
            dragger.removeWidget.connect(container.removeWidget)
            dragger.showWidgetSettings.connect(container.showWidgetSettings)
        } else {
            console.debug("Cannot create the widget from file WidgetDragger.qml" +
                          "\nerror : " + component.errorString())
        }
        component.destroy()
    }

    // Remove widget
    // This slot is connected to the remove widget
    // button on the dragger
    function removeWidget(widget) {
        draggerManager.unregisterDragger(widget)
        WidgetsPageListModelInstance.removeWidget(WidgetsPageListModelInstance.currentPage, widget)
    }

    Component.onCompleted: DragManagerInstance.gridManager = widgetsView.gridManagerInstance

    Connections {
        target: DragManagerInstance
        onRequestDisableDraggers: draggerManager.disableDraggers()
        onRequestCreateDragger: createDragger(widgetProperties)
        onRequestDeleteDraggers: draggerManager.unregisterDraggers()
    }
}
