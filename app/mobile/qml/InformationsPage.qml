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
import "UiConstants.js" as Ui

AbstractNavigationPage {
    id: container
    title: qsTr("Informations")
    model: ListModel {
        ListElement {
            identifier: "showPackageList"
            text: QT_TR_NOOP("Installed packages")
        }
        ListElement {
            identifier: "showDockList"
            text: QT_TR_NOOP("Installed docks")
        }
        ListElement {
            identifier: "showWidgetList"
            text: QT_TR_NOOP("Installed widgets")
        }
    }
    onShow: {
        if(page == "showPackageList") {
//            window.pageStack.push(packageListPage)
        }
        if(page == "showDockList") {
            window.pageStack.push(dockListPage)
        }
        if(page == "showWidgetList") {
            window.pageStack.push(widgetListPage)
        }
    }

//    PackageListPage {
//        id: packageListPage
//    }
    DockListPage {
        id: dockListPage
    }
    WidgetListPage {
        id: widgetListPage
    }

    tools: ToolBarLayout {
        ToolIcon { iconId: "toolbar-back"; onClicked: window.pageStack.pop() }
    }
}

