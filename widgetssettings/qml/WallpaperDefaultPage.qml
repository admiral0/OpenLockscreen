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
import QtMobility.gallery 1.1

AbstractPage {
    id: container
    property string selected
    property string newSelected
    property string prefix: "/opt/widgets/data/"

    title: qsTr("Default wallpapers")
    tools: ToolBarLayout {
        ToolButtonRow {
            ToolButton {
                text: qsTr("Save")
                enabled: false
                visible: container.selected != container.newSelected
            }
            ToolButton {
                text: qsTr("Save")
                visible: container.selected == container.newSelected
                onClicked: {
                    settingsManager.wallpaperSource = container.newSelected
                    window.pageStack.pop()
                }
            }
            ToolButton {
                text: qsTr("Cancel")
                onClicked: window.pageStack.pop()
            }
        }
    }

    content: Item {
        anchors.fill: parent
        GridView {
            width: container.width
            height: container.height - 70
            clip: true
            model: model
            cellHeight: 160
            cellWidth: 160

            delegate: Item {
                height: 160
                width: 160
                property bool selected: container.prefix + model.url == container.selected

                Rectangle {
                    id: selectedRectangle
                    anchors.fill: parent
                    visible: false
                    color: "#6193CF"
                }

                Image {
                    id: image
                    width: parent.width; height: parent.height
                    anchors.centerIn: parent
                    asynchronous: true
                    smooth: true
                    source: container.prefix + model.thumbUrl
                }

                states: State {
                    name: "selected"; when: selected
                    PropertyChanges {
                        target: selectedRectangle
                        visible: true
                    }
                    PropertyChanges {
                        target: image
                        scale: 0.95
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        container.selected = container.prefix + model.url
                        container.newSelected = container.prefix + model.url
                    }
                }
            }
        }

        ListModel {
            id: model
            ListElement {
                thumbUrl: "wallpaper-1-thumbnail.jpg"
                url: "wallpaper-1.jpg"
            }
            ListElement {
                thumbUrl: "wallpaper-2-thumbnail.jpg"
                url: "wallpaper-2.jpg"
            }
            ListElement {
                thumbUrl: "wallpaper-3-thumbnail.jpg"
                url: "wallpaper-3.jpg"
            }
            ListElement {
                thumbUrl: "wallpaper-4-thumbnail.jpg"
                url: "wallpaper-4.jpg"
            }
        }
    }
}
