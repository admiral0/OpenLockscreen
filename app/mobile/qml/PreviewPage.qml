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
import org.SfietKonstantin.widgets 1.0
//import org.SfietKonstantin.widgets.docks 1.0
//import org.SfietKonstantin.widgets.background 1.0

Page {
    id: mainPage
    orientationLock: PageOrientation.LockPortrait

    PinchArea {
        anchors.fill: parent
        onPinchFinished: window.pageStack.pop()
    }

    /*
    Background {
        anchors.fill: parent
        id: background
        // Currently disabled because of bugs in PageView
        // view: widgetsPage.view
        // initialX: widgetsPage.initialX
    }

    DockedView {
        content: Item {
            id: widgets
            anchors.fill: parent

            WidgetsHorizontalPageView {
                id: widgetsPage
            }
        }
    }*/

    // Testing
    WidgetsHorizontalPageView {
        id: widgetsPage
    }

    MouseArea {
        anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.right: parent.right
        height: 100

        onClicked: {
            var list = provider.registeredWidgets()
            var widgetFile = list[0]

            var widget = provider.widget(widgetFile)
            WidgetsPageListModelInstance.addWidget(0, widget, widgetsPage.gridManagerInstance)
        }
    }
}
