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
import org.SfietKonstantin.widgets.info.dock 1.0
import "UiConstants.js" as Ui

AbstractPage {
    id: container
    title: qsTr("Edit docks")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                window.pageStack.pop()
                remoteSettingsManager.reloadDocks()
            }
        }
        ToolButton {
            anchors.centerIn: parent
            text: qsTr("Add dock")
            onClicked: addDockSheet.open()
        }
    }
    onVisibleChanged: {
        if (!visible) {
            listView.positionViewAtBeginning()
        }
    }

    content: ListView {
        id: listView
        property QtObject selectedDock
        anchors.fill: parent
        model: DockModelInstance
        clip: true


        delegate: ClickableEntry {
            text: ProviderManagerInstance.provider.dockName(model.dock.fileName,
                                                            model.dock.disambiguation)
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
                providerManager: ProviderManagerInstance
            }
            clip: true
            delegate: ClickableEntry {
                text: model.name
                subText: model.description
                indicatorIcon: ""
                onClicked: {
                    if (DockModelInstance.hasDock(model.file, model.disambiguation)) {
                        dockPresent.open()
                        addDockSheet.reject()
                        return
                    }

                    var dock = ProviderManagerInstance.provider.dock(model.file,
                                                                     model.disambiguation)
                    DockModelInstance.addBaseDock(dock)
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
                onClicked: {
                    DockModelInstance.removeDock(listView.selectedDock)
                }
            }
        }
    }

    QueryDialog {
        id: dockPresent
        titleText: qsTr("The dock is already present")
        message: qsTr("The dock you are trying to add is already present. Only one dock of\
each type can be added.")
        acceptButtonText: qsTr("Close")
    }
}
