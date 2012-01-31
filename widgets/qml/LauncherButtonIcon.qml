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
import "UiConstants.js" as UI

// Icon used in launcher button
// This icon is used to represent either
// an application or a folder.
Item {
    id: container
    width: UI.ICON_SIZE_XLARGE; height: UI.ICON_SIZE_XLARGE
    property alias source: background.source
    property alias sub1Source: sub1.source
    property alias sub2Source: sub2.source
    property alias sub3Source: sub3.source
    property alias sub4Source: sub4.source

    Rectangle {
        id: backgroundRectangle
        anchors.fill: icon
        color: colors.green5
        radius: 32
        opacity: 1

        states: State {
            name: "hidden"; when: background.status == Image.Ready
            PropertyChanges {
                target: backgroundRectangle
                opacity: 0
            }
        }

        Behavior on opacity {
            NumberAnimation {duration: UI.ANIMATION_DURATION_FAST}
        }
    }

    Image {
        id: background
        anchors.fill: parent
        sourceSize.width: UI.ICON_SIZE_XLARGE; sourceSize.height: UI.ICON_SIZE_XLARGE
        opacity: 0

        states: State {
            name: "visible"; when: background.status == Image.Ready
            PropertyChanges {
                target: background
                opacity: 1
            }
        }

        Behavior on opacity {
            NumberAnimation {duration: UI.ANIMATION_DURATION_FAST}
        }
    }

    Image {
        id: sub1
        anchors.top: parent.top; anchors.topMargin: UI.ICON_FOLDER_MARGIN
        anchors.left: parent.left; anchors.leftMargin: UI.ICON_FOLDER_MARGIN
        width: UI.ICON_SIZE_SMALL; height: UI.ICON_SIZE_SMALL
        sourceSize.width: UI.ICON_SIZE_XLARGE; sourceSize.height: UI.ICON_SIZE_XLARGE
        opacity: 0

        states: State {
            name: "visible"; when: sub1.status == Image.Ready
            PropertyChanges {
                target: sub1
                opacity: 1
            }
        }

        Behavior on opacity {
            NumberAnimation {duration: UI.ANIMATION_DURATION_FAST}
        }
    }

    Image {
        id: sub2
        anchors.top: parent.top; anchors.topMargin: UI.ICON_FOLDER_MARGIN
        anchors.right: parent.right; anchors.rightMargin: UI.ICON_FOLDER_MARGIN
        width: UI.ICON_SIZE_SMALL; height: UI.ICON_SIZE_SMALL
        sourceSize.width: UI.ICON_SIZE_XLARGE; sourceSize.height: UI.ICON_SIZE_XLARGE
        opacity: 0

        states: State {
            name: "visible"; when: sub2.status == Image.Ready
            PropertyChanges {
                target: sub2
                opacity: 1
            }
        }

        Behavior on opacity {
            NumberAnimation {duration: UI.ANIMATION_DURATION_FAST}
        }
    }

    Image {
        id: sub3
        anchors.bottom: parent.bottom; anchors.bottomMargin: UI.ICON_FOLDER_MARGIN
        anchors.left: parent.left; anchors.leftMargin: UI.ICON_FOLDER_MARGIN
        width: UI.ICON_SIZE_SMALL; height: UI.ICON_SIZE_SMALL
        sourceSize.width: UI.ICON_SIZE_XLARGE; sourceSize.height: UI.ICON_SIZE_XLARGE
        opacity: 0

        states: State {
            name: "visible"; when: sub3.status == Image.Ready
            PropertyChanges {
                target: sub3
                opacity: 1
            }
        }

        Behavior on opacity {
            NumberAnimation {duration: UI.ANIMATION_DURATION_FAST}
        }
    }

    Image {
        id: sub4
        anchors.bottom: parent.bottom; anchors.bottomMargin: UI.ICON_FOLDER_MARGIN
        anchors.right: parent.right; anchors.rightMargin: UI.ICON_FOLDER_MARGIN
        width: UI.ICON_SIZE_SMALL; height: UI.ICON_SIZE_SMALL
        sourceSize.width: UI.ICON_SIZE_XLARGE; sourceSize.height: UI.ICON_SIZE_XLARGE
        opacity: 0

        states: State {
            name: "visible"; when: sub4.status == Image.Ready
            PropertyChanges {
                target: sub4
                opacity: 1
            }
        }

        Behavior on opacity {
            NumberAnimation {duration: UI.ANIMATION_DURATION_FAST}
        }
    }
}
