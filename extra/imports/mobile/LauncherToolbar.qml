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
import org.SfietKonstantin.mobile.launcher 1.0
import org.SfietKonstantin.widgets.colors 1.0
import "UiConstants.js" as Ui

Item  {
    width: Ui.TOOLBAR_WIDTH
    height: Ui.TOOLBAR_HEIGNT

    Image {
        anchors.fill: parent
        source: "toolbar.png"
    }

    Item {
        anchors.centerIn: parent
        width: Ui.ICON_SIZE_DEFAULT
        height: Ui.ICON_SIZE_DEFAULT

        Rectangle {
            visible: mouseArea.pressed
            anchors.fill: parent
            radius: 5
            color: Colors.aluminiumGray4
        }

        Image {
            anchors.fill: parent
            source: "home.png"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: LauncherManagerInstance.visible = false
        }
    }

}
