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
    width: 330
    height: 200

    AlignedTimer {
//    Timer {
        id: timer
        minimumInterval: 1
        maximumInterval: 1
//        interval: 16
        singleShot: false
        onTimeout: clock.changeTime()
//        onTriggered: clock.changeTime()
        Component.onCompleted: start()
    }


    Item {
        width: clock.width
        height: time.height + 4 + date.height
        anchors.top: parent.top; anchors.topMargin: 15

        Text {
            id: time
            anchors.right: parent.right; anchors.rightMargin: 10
            anchors.top: parent.top
            font.pixelSize: 90
            color: Colors.white
            style: Text.Outline
            styleColor: Colors.aluminiumGray4
        }

        Text {
            id: date
            anchors.right: parent.right; anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            font.pixelSize: 18
            color: Colors.white
            style: Text.Outline
            styleColor: Colors.aluminiumGray4
        }
    }




}
