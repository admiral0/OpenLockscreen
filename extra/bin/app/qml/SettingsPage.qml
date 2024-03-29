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
//import com.nokia.extras 1.1
import "UiConstants.js" as Ui

AbstractNavigationPage {
    id: container
    orientationLock: PageOrientation.LockPortrait
    title: qsTr("Configure widgets")
    tools: ToolBarLayout {
        ToolIcon { iconId: "toolbar-back"; onClicked: window.pageStack.pop() }
    }

    onShow: {
        if(page == "showDockEditor") {
            window.pageStack.push(dockEditorPage)
        }
        if(page == "showWidgetEditor") {
            window.pageStack.push(widgetEditorPage)
        }
        if(page == "showBackgroundEditor") {
            window.pageStack.push(backgroundEditorPage)
        }
    }
    model: ListModel {
        ListElement {
            identifier: "showDockEditor"
            text: QT_TR_NOOP("Edit docks")
        }
        ListElement {
            identifier: "showWidgetEditor"
            text: QT_TR_NOOP("Edit widgets")
        }
        ListElement {
            identifier: "showBackgroundEditor"
            text: QT_TR_NOOP("Edit background")
        }
    }

    DockEditorPage {
        id: dockEditorPage
    }

    WidgetEditorPage {
        id: widgetEditorPage
    }

//    BackgroundEditorPage {
//        id: backgroundEditorPage
//        onBackgroundChanged: {
//            widgetEditorPage.updateBackground()
//            previewPage.updateBackground()
//            remoteSettingsManager.reloadSettings("background")
//        }
//    }
}
