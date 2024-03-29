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
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.colors 1.0
import QtMobility.systeminfo 1.2

Widget {
    id: clock
    onEnabledChanged: {
        enabled ? timer.start() : timer.stop()
        if (enabled) {
            changeTime()
        }
    }
    Component.onCompleted: changeTime()
    function changeTime() {
        var dateTime = new Date
        time.text = Qt.formatTime(dateTime)
        date.text = Qt.formatDate(dateTime, Qt.DefaultLocaleLongDate)
    }
    width: 460
    height: 200

     AlignedTimer {
         id: timer
         minimumInterval: 1
         maximumInterval: 1
         singleShot: false
         onTimeout: clock.changeTime()
         Component.onCompleted: start()
     }

    Rectangle {
        id: background
        anchors.fill: parent
        radius: 10
        border.color: Colors.aluminiumGray5
        border.width: 3
        opacity: 0.9
        gradient: Gradient {
            GradientStop {position: 0; color: Colors.aluminiumGray6}
            GradientStop {position: 1; color: Colors.black}
        }
    }

    Item {
        width: background.width
        height: time.height + 7 + date.height
        anchors.centerIn: background

        Text {
            id: time
            anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top
            font.pixelSize: 85
            color: Colors.white
            style: Text.Outline
            styleColor: Colors.black
        }

        Text {
            id: date
            anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom
            font.pixelSize: 30
            color: Colors.white
            style: Text.Outline
            styleColor: Colors.black
        }
    }




}
