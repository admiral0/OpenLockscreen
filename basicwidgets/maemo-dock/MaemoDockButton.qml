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


Item {
    id: container
    signal clicked()
    width: 100

    Rectangle {
        id: clickFeedback
        anchors.fill: parent
        visible: false
        opacity: 0.9
        color: Colors.gray2
    }

    Image {
        id: maemoMenuIcon
        anchors.centerIn: parent
        width: 60
        height: 30
        source: "maemo-menu.png"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: clickFeedback.visible = true
        onReleased: clickFeedback.visible = false
        onClicked: container.clicked()
    }
}
