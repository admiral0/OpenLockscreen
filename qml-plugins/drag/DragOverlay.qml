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
    anchors.fill: widgetsView

    DraggerManager {
        id: draggerManager
    }

    Item {
        id: contentsContainer
        parent: widgetsView.contentItem
        anchors.fill: parent
    }

    // Create a dragger
    function createDragger(widget) {
        var qmlFile = PackageManagerInstance.widgetFile(widget.packageIdentifier, widget.fileName)
        var component = Qt.createComponent("WidgetDragger.qml")
        if (component.status == Component.Ready) {
//            var dragRect = Qt.rect(0,0, grid.width, grid.height)
            var dragger = component.createObject(contentsContainer,
                                                 {"widget": widget,
                                                  "qmlFile": qmlFile});
            draggerManager.registerDragger(widget, dragger)
//            dragger.removeWidget.connect(container.removeWidget)
//            dragger.showWidgetSettings.connect(container.showWidgetSettings)
        } else {
            console.debug("Cannot create the widget from file WidgetDragger.qml" +
                          "\nerror : " + component.errorString())
        }
        component.destroy()
    }

    Connections {
        target: DragManagerInstance
        onRequestCreateDragger: createDragger(widget)
        onRequestDeleteDraggers: draggerManager.unregisterDraggers()
    }
}

/*
Item {
    id: container
    property int gridWidth
    property int gridHeight
    property real unlockedViewScale

    // Create a dragger
    function createDragger(widget) {
        var component = Qt.createComponent("WidgetDragger.qml")
        if (component.status == Component.Ready) {
            var dragRect = Qt.rect(0,0, grid.width, grid.height)
            var dragger = component.createObject(grid,
                                                 {"z": 1000,
                                                  "widget": widget,
                                                  "dragRect": dragRect});
            viewManager.registerDragger(widget, dragger)
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
        var pageModel = displayedPagesModel.pageModel(viewManager.currentPageIndex)
        pageModel.removeWidget(widget)
        viewManager.unregisterDragger(widget)
    }

    // Show widget settings
    // This slot is connected to the show
    // widget settings button on the dragger
    function showWidgetSettings(widget) {
        viewManager.showWidgetSettings(widget)
    }

    scale: 1
    y: 0

    // This is a false grid that is over
    // the views and is used to drag
    // the draggers.
    Item {
        id: grid
        anchors.centerIn: parent
        width: container.gridWidth
        height: container.gridHeight

        Rectangle {
            id: highlightRect
            x: viewManager.highlightRect.x
            y: viewManager.highlightRect.y
            width: viewManager.highlightRect.width
            height: viewManager.highlightRect.height
            radius: 6
            smooth: true
            opacity: 0.8
            visible: viewManager.currentDraggedWidget != ""
        }
    }

    Connections {
        target: viewManager
        onRequestCreateDragger: createDragger(widget)
    }

    states: State {
        name: "unlocked"; when: !viewManager.locked
        PropertyChanges {
            target: container
            scale: container.unlockedViewScale
            y: - view.height * 0.5 * (1- unlockedViewScale) + UI.MARGIN_DEFAULT
        }
    }

    Behavior on scale {
        NumberAnimation {
            duration: UI.ANIMATION_DURATION_FAST
        }
    }

    Behavior on y {
        NumberAnimation {
            duration: UI.ANIMATION_DURATION_FAST
        }
    }
}*/
