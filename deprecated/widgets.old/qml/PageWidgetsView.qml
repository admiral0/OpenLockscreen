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
import com.nokia.meego 1.0
import org.sk.widgets 1.0
import "UiConstants.js" as UI

// Widget page
// This widget page is
// used to display the widgets
Item {
    id: container
    property real unlockedViewScale
    property variant pageModel
    property int gridWidth
    property int gridHeight

    width: view.width
    height: view.height
    scale: 1
    y: 0

    PageWidgetsBackground {
        width: container.width + 20
        height: container.height + 20
        anchors.centerIn: parent
    }

    Item {
        id: grid
        width: container.gridWidth
        height: container.gridHeight
        anchors.centerIn: parent

        Repeater {
            id: repeater
            model: container.pageModel
            anchors.fill: parent
            delegate: WidgetContainer {
                id: delegate
                property bool isBeingDragged: false

                // Check if the widget is being dragged
                function checkIsBeingDragged() {
                    if(viewManager.currentDraggedWidget == model.widget.identifier) {
                        isBeingDragged = true
                    } else {
                        isBeingDragged = false
                    }
                }

                // Update the widget position
                // This function updates the widget position
                // based on the highilighter
                // It will do this only when the widget is being dragged
                function updateWidget() {
                    if(isBeingDragged) {
                        var highlightRect = viewManager.highlightRect
                        repeater.model.updateWidget(model.widget.identifier, highlightRect.x,
                                                    highlightRect.y,
                                                    highlightRect.width,
                                                    highlightRect.height)
                    }
                    checkIsBeingDragged()
                }

                // Check if need to show settings
                // This function checks if the widget
                // have to show it's settings
                function checkShowSettings(identifier) {
                    if(identifier == model.widget.identifier && model.widget.hasSettings) {
                        showSettings()
                    }
                }

                x: model.widget.x
                y: model.widget.y
                z: model.widget.z
                settings: model.widget.settings
                width: model.widget.width
                height: model.widget.height
                qmlFile: model.widget.qmlFile
                visible: viewManager.currentDraggedWidget != model.widget.identifier

                // When the widget needs to update
                // it's geometry
                onRequireUpdateGeometry: {
                    repeater.model.updateWidget(model.widget.identifier, x, y, width, height)
                }

                Connections {
                    target: viewManager
                    onCurrentDraggedWidgetChanged: {
                        updateWidget()
                    }
                    onRequestShowWidgetSettings: {
                        checkShowSettings(identifier)
                    }
                }
            }
        }
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
}
