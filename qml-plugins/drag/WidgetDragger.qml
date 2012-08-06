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
//import "UiConstants.js" as UI

// Widget dragger
// This widget dragger is used to drag
// a widget. It makes a graphic copy of the
// widget to move and when it is dragged, the
// widget to move is hidden, and the copy of
// the widget is shown. Then, the used has the
// impression of moving the widget.
//
// When the dragger is released, the true widget
// is set at the correct position
Item {
    id: container
    property variant widget
    property variant dragRect
    property string qmlFile
    property bool dragging
    signal removeWidget(variant widget)
//    signal showWidgetSettings(variant widget)
    opacity: 0.8


    // This function is used to update
    // the highlighter when the dragger
    // is moving
    function drag() {
        if(dragging) {
            DragManagerInstance.drag(widget, Qt.rect(x, y, width, height))
//            var pos = viewManager.computeWidgetPosition(x, y)
//            viewManager.highlightRect = Qt.rect(pos.x, pos.y, width, height)
        }
    }

    function finishDrag() {
        if (!dragging) {
            DragManagerInstance.finishDrag(widget, container, Qt.rect(x, y, width, height))
        }
    }

    /*
    // This function is used to
    // update the information about
    // the widget that is currently being dragged
    function updateDraggedWidgetIdentifierAndPosition() {
        if(dragging) {
            viewManager.currentDraggedWidget = widget.identifier
        } else {
            // When the dragger is released,
            // the current position is passed
            // to the widget object, that is used
            // to store the position of the widget
            viewManager.currentDraggedWidget = ""
            x = widget.x
            y = widget.y
            width = widget.width
            height = widget.height
        }
    }
    */
    Component.onCompleted: {
        x = widget.x
        y = widget.y
        width = widget.width
        height = widget.height
    }

    onXChanged: drag()
    onYChanged: drag()
    onDraggingChanged: {
        drag()
        finishDrag()
//        updateDraggedWidgetIdentifierAndPosition()
    }


    WidgetContainer {
        id: widgetContainer
        qmlFile: container.qmlFile
        widgetProperties: widget
        visible: false
        anchors.fill: parent
    }


    MouseArea {
        anchors.fill: parent
        drag.target: container
        drag.minimumX: 0
        drag.minimumY: 0
        drag.maximumX: container.parent.width - container.width
        drag.maximumY: container.parent.height - container.height
        drag.axis: Drag.XandYAxis

        onPressed: container.dragging = true
        onReleased: container.dragging = false
    }

    WidgetDraggerButton {
        id: removeButton
        anchors.top: container.top; anchors.topMargin: - 60
        anchors.right: container.right; anchors.rightMargin: - 60
        source: DragParametersInstance.removeButtonSource
        onClicked: container.removeWidget(container.widget)
    }
    /*
//    WidgetDraggerButton {
//        id: settingsButton
//        anchors.bottom: container.bottom; anchors.bottomMargin: - UI.MARGIN_DEFAULT
//        anchors.left: container.left; anchors.leftMargin: - UI.MARGIN_DEFAULT
//        source: "image://theme/icon-l-settings"
//        visible: container.widget.hasSettings
//        onClicked: container.showWidgetSettings(container.widget)
//    }
    */
    states: State {
        name: "dragging"; when: dragging
        PropertyChanges {
            target: widgetContainer
            visible: true
        }
    }

}
