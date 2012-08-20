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
import QtMobility.gallery 1.1
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.colors 1.0

SettingsItem {
    id: container
    anchors.fill: parent
    clip: true
    property string selected: ""

    Connections {
        target: WidgetConfigurationHelperInstance
        onSaveSettingsRequested: {
            var settings = new Object
            settings.picture = selected
            WidgetConfigurationHelperInstance.saveSettings(widget, settings)
            container.selected = ""
        }
    }

    GridView {
        anchors.fill: parent

        model: model

        cellHeight: 160
        cellWidth: 160

        delegate: Item {
            height: 160
            width: 160
            property bool selected: model.url == container.selected

            Rectangle {
                id: selectedRectangle
                anchors.fill: parent
                visible: false
                color: Colors.skyBlue2
            }

            Image {
                id: image
                width: parent.width; height: parent.height
                anchors.centerIn: parent
                asynchronous: true
                smooth: true
                source: "file:///home/user/.thumbnails/grid/" + Qt.md5(model.url) + ".jpeg"
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
                onClicked: container.selected = model.url
            }
        }
    }

    DocumentGalleryModel {
        id: model
        rootType: DocumentGallery.Image
        properties: ["url"]
        filter: GalleryWildcardFilter {
            property: "fileName";
            value: "*.jpg";
        }
    }
}

