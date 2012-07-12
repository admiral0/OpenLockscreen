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

import QtQuick 1.0
import org.sk.widgets 1.0
import com.nokia.meego 1.0

Widget {
    width: 400
    height: 100

    Image {
        id: meegon
        width: 80; height: 100
        sourceSize.width: 80; sourceSize.height: 100
        source: "data/welcome.png"

        MouseArea {
            anchors.fill: parent
            onClicked: text.index = (text.index + 1) % 13
        }
    }

    BorderImage {
        id: bubble
        source: "data/chat-bubble.svg"
        anchors.left: meegon.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        border.left: 50; border.top: 50
        border.right: 20; border.bottom: 50

        Item {
            anchors.top: parent.top; anchors.topMargin: 10
            anchors.bottom: parent.bottom; anchors.bottomMargin: 10
            anchors.left: parent.left; anchors.leftMargin: 48
            anchors.right: parent.right; anchors.rightMargin: 10

            Label {
                id: text
                anchors.fill: parent
                property int index: 0
                textFormat: Text.RichText
                verticalAlignment: Text.AlignVCenter
                text: {
                    if(index == 0) {
                        qsTr("<p><bold>Welcome</bold></p><p><small>Touch me to see the next hint.</small></p>")
                    } else if(index == 1) {
                        qsTr("<p><bold>Launch applications</bold></p><p><small>Click on the menu to show the application launcher.</small></p>")
                    } else if(index == 2) {
                        qsTr("<p><bold>I'm a widget</bold></p><p><small>You can add more widgets to customize your phone.</small></p>")
                    } else if(index == 3) {
                        qsTr("<p><bold>Unlock widgets</bold></p><p><small>Unlock the widgets by pinching the view out.</small></p>")
                    } else if(index == 4) {
                        qsTr("<p><bold>Add new widgets</bold></p><p><small>You can add new widgets by clicking on \"add widget\".</small></p>")
                    } else if(index == 5) {
                        qsTr("<p><bold>Add shortcuts</bold></p><p><small>You can add shortcuts to applications and contacts.</small></p>")
                    } else if(index == 6) {
                        qsTr("<p><bold>Edit widgets</bold></p><p><small>Some widgets can be edited by clicking on the wrench.</small></p>")
                    } else if(index == 7) {
                        qsTr("<p><bold>Remove widgets</bold></p><p><small>You can remove widgets by clicking on the red cross.</small></p>")
                    } else if(index == 8) {
                        qsTr("<p><bold>Moving widgets</bold></p><p><small>Feel free to organize the widgets by dragging them.</small></p>")
                    } else if(index == 9) {
                        qsTr("<p><bold>Lock widgets</bold></p><p><small>Lock the widgets by pinching the view in.</small></p>")
                    } else if(index == 10) {
                        qsTr("<p><bold>Advanced settings</bold></p><p><small>A separated application is used to customize the view.</small></p>")
                    } else if(index == 11) {
                        qsTr("<p><bold>Advanced settings</bold></p><p><small>In this application, you can change wallpaper, docks ...</small></p>")
                    } else if(index == 12) {
                        qsTr("<p><bold>I'm finished</bold></p><p><small>You can now remove me :)</small></p>")
                    }
                }
            }
        }
    }
}
