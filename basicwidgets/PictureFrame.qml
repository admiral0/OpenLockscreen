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
import org.sk.widgets 1.0

Widget {
    id: container
    function checkSettings() {
        if(settings.value("picture") != undefined) {
            placeHolderText.visible = false
            settingsSheet.selected = settings.value("picture")
            picture.source = settings.value("picture")
        } else {
            placeHolderText.visible = true
            picture.source = ""
        }
    }
    width: 200; height: 200
    onShowSettings: settingsSheet.open()
    clip: true

    Rectangle {
        color: colors.aluminiumGray2
        anchors.fill: parent
        opacity: 0.8
        radius: 10
    }

    Rectangle {
        id: placeHolder
        width: 190
        height: 190
        anchors.centerIn: container
        color: colors.brownOrange1

        Text {
            id: placeHolderText
            font.pixelSize: 30
            text: qsTr("You can set a photo to this picture frame")
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }
    }

    Image {
        scale: 0
        id: picture
        width: 190
        height: 190
        sourceSize.width: 400
        asynchronous: true
        anchors.centerIn: container
        fillMode: Image.PreserveAspectCrop
        clip: true

        states: State {
            name: "loaded"; when: picture.status == Image.Ready
            PropertyChanges {
                target: picture
                scale: 1
            }
        }

        Behavior on scale {
            NumberAnimation {duration: 1000; easing.type: Easing.OutBack }
        }
    }

    PictureFrameSettingsSheet {
        id: settingsSheet
        onAccepted: {
            settings.setValue("picture", selected)
        }
    }

    Component.onCompleted: container.checkSettings()

    Connections {
        target: settings
        onSettingsChanged: container.checkSettings()
    }
}

