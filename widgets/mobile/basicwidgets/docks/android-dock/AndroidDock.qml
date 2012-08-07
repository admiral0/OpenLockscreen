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

Dock {
    id: container
    height: 100
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right
//    settingsEnabled: true

    Item {
        id: bar
        width: 270
        height: 90
        opacity: 0.9
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Rectangle {
            id: barBackground
            anchors.fill: parent
            color: Colors.gray6
            radius: 6
        }

        AndroidDockButton {
            id: callButton
            width: 90
            height: 90
            icon: "android-call.png"
//            onClicked: {
//                launcherManager.launchApplication("/usr/bin/invoker --type=m /usr/bin/call-history")
//            }
        }

        AndroidDockButton {
            id: menuButton
            anchors.left: callButton.right
            width: 90
            height: 90
            icon: "android-menu.png"
//            onClicked: launcherManager.launcherVisible = true
        }
        AndroidDockButton {
            id: internetButton
            anchors.left: menuButton.right
            width: 90
            height: 90
            icon: "android-internet.png"
//            onClicked: {
//                launcherManager.launchApplication("/usr/bin/invoker --type=m /usr/bin/grob")
//            }
        }
    }

//    Item {
//        id: leftDesktopCountcontainer
//        height: parent.height
//        anchors.left: parent.left; anchors.right: bar.left

//        Row {
//            anchors.centerIn: parent
//            spacing: 5
//            Repeater {
//                model: api.currentPage
//                delegate: Rectangle {
//                    width: 10; height: 10
//                    radius: 5
//                    opacity: 0.8
//                    smooth: true
//                }
//            }
//        }
//    }

//    Item {
//        id: rightDesktopCountcontainer
//        height: parent.height
//        anchors.left: bar.right; anchors.right: parent.right

//        Row {
//            anchors.centerIn: parent
//            spacing: 5
//            Repeater {
//                model: api.pagesCount - api.currentPage - 1
//                delegate: Rectangle {
//                    width: 10; height: 10
//                    radius: 5
//                    opacity: 0.8
//                    smooth: true
//                }
//            }
//        }
//    }
}
