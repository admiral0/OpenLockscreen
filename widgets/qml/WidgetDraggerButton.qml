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
import "UiConstants.js" as UI

// Dragger button
// This button is used on
// widgets draggers to
// provide actions to the user.
Item {
    id: container
    signal clicked
    property alias source: icon.source

    width: UI.WIDGET_BUTTON_SIZE
    height: UI.WIDGET_BUTTON_SIZE

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: container.clicked()
    }

    Image {
        id: icon
        anchors.fill: parent
        smooth: true
    }

    states: [
        State {
            name: "clicked"; when: mouseArea.pressed
            PropertyChanges {
                target: container
                scale: 0.9
            }
        }
    ]
}
