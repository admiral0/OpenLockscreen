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

// Alternative toolbar used
// to display tools for the
// unlocked widgets view
ToolBar {
    id: container
    anchors.bottom: parent.bottom
    signal addWidgetClicked()
    signal menuClicked()
    signal homeClicked()
    function setWidgetLayout() {
        container.tools = widgetLayout
    }
    function setNullLayout() {
        container.tools = null
    }

    // Toolbar layout
    // used for widget editing
    ToolBarLayout {
        id: widgetLayout
        visible: false
        ToolButton {
            anchors.centerIn: parent
            text: qsTr("Add widget")
            onClicked: container.addWidgetClicked()
        }
        ToolIcon {
            iconId: "toolbar-view-menu"
            onClicked: container.menuClicked()
        }
    }

//    // Toolbar layout
//    // used for the application launcher
//    ToolBarLayout {
//        id: launcherLayout
//        visible: false
//        ToolIcon {
//            anchors.centerIn: parent
//            iconId: "toolbar-home"
//            onClicked: container.homeClicked()
//        }
//    }
}
