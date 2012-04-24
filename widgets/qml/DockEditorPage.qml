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
import org.SfietKonstantin.widgets.extra 1.0
import "UiConstants.js" as Ui

AbstractPage {
    id: container
    title: qsTr("Edit docks")
    tools: ToolBarLayout {
        ToolIcon { iconId: "toolbar-back"; onClicked: window.pageStack.pop() }
        ToolButton {
            anchors.centerIn: parent
            text: qsTr("Add dock")
            onClicked: addDockSheet.open()
        }
    }

    content: ListView {
        id: listView
        property QtObject selectedDock
        anchors.fill: parent
        model: DockModelInstance
        clip: true


        delegate: ClickableEntry {
            text: model.dock.name
            indicatorIcon: ""
            onPressAndHold: {
                listView.selectedDock = model.dock
                deleteDock.open()
            }
        }
    }

    Sheet {
        id: addDockSheet
        rejectButtonText: qsTr("Cancel")
        content: ListView {
            id: view
            anchors.fill: parent
            model: DockInformationModel {
                packageManager: PackageManagerInstance
            }
            clip: true
            delegate: ClickableEntry {
                text: model.name
                subText: model.description
                indicatorIcon: ""
                onClicked: {
                    var dock = PackageManagerInstance.dock(model.package, model.file)
                    DockModelInstance.addDock(dock)
                    addDockSheet.accept()
                }
            }
        }
    }

    Menu {
        id: deleteDock
        MenuLayout {
            MenuItem {
                text: qsTr("Delete dock")
                onClicked: console.debug(DockModelInstance.removeDock(listView.selectedDock))
            }
        }
    }
}
