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
import org.SfietKonstantin.widgets.colors 1.0
import "UiConstants.js" as Ui

// Button used for a launcher
// This button is used to represent an
// application or a folder in the application
// launcher.
Item  {
    id: container
    property alias icon: icon.source
    property alias sub1Icon: icon.sub1Source
    property alias sub2Icon: icon.sub2Source
    property alias sub3Icon: icon.sub3Source
    property alias sub4Icon: icon.sub4Source
    property alias name: text.text
    signal clicked
    width: Ui.APPLICATION_LAUNCHER_WIDTH
    height: Ui.APPLICATION_LAUNCHER_HEIGHT

    Item {
        id: iconContainer
        width: parent.width
        height: icon.height + Ui.MARGIN_DEFAULT + text.height

        LauncherButtonIcon {
            id: icon
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: text
            anchors.top: icon.bottom
            anchors.topMargin: Ui.MARGIN_SMALL
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: Ui.FONT_SIZE_XXSMALL
            wrapMode: Text.NoWrap
            elide: Text.ElideRight
            color: Colors.white
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: container.clicked()
    }

    states: State {
        name: "clicked"; when: mouseArea.pressed
        PropertyChanges {
            target: container
            scale: 0.9
        }
    }

    Behavior on scale {
        NumberAnimation { duration: Ui.ANIMATION_DURATION_XFAST }
    }
}
