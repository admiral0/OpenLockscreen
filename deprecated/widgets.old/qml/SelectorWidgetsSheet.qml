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
import org.sk.widgets 1.0
import "UiConstants.js" as UI
import "LauncherButtonIconFunctions.js" as LBIFunctions

// Widgets selector
// This sheet contains all the available
// widgets as well as applications shortcuts
// and provides signals to notify an add
Sheet {
    id: container
    signal addWidget(variant widget, variant settings)
    signal addApplicationShortcut(variant shortcut)
    rejectButtonText: qsTr("Cancel")

    onStatusChanged: {
        if(status == DialogStatus.Closed) {
            while(pageStack.depth > 1) {
                pageStack.pop()
            }
        }
    }

    content: Item {
        anchors.fill: parent
        PageStack {
            id: pageStack
            anchors.top: parent.top
            anchors.bottom: toolbar.top
            anchors.left: parent.left
            anchors.right: parent.right
            Component.onCompleted: pageStack.push(mainPage, true)
            toolBar: toolbar

            Page {
                id: mainPage
                tools: null
                clip: true
                orientationLock: settingsWrapper.orientation == "landscape" ?
                                 PageOrientation.LockLandscape: PageOrientation.LockPortrait

                SelectorModel {
                    id: listModel
                    Component.onCompleted: {
                        addEntry("addWidget", qsTr("Add Widget"))
                        addEntry("addAppShortcut", qsTr("Add application shortcut"))
                    }
                }

                ListView {
                    anchors.fill: parent
                    model: listModel
                    delegate: ClickableEntry {
                        text: model.text
                        onClicked: {
                            if(model.identifier == "addWidget") {
                                pageStack.push(widgetPage)
                            } else if(model.identifier == "addAppShortcut") {
                                pageStack.push(applicationShortcutPage)
                            }
                        }
                    }
                }
            }

            Page {
                id: widgetPage
                tools: backLayout
                clip: true
                orientationLock: settingsWrapper.orientation == "landscape" ?
                                 PageOrientation.LockLandscape: PageOrientation.LockPortrait

                ListView {
                    anchors.fill: parent
                    model: availableWidgetsModel
                    delegate: ClickableEntry {
                        text: model.widget.name
                        indicatorIcon: ""
                        onClicked: {
                            var object
                            container.addWidget(model.widget, object)
                            container.accept()
                        }
                    }
                }
            }

            Page {
                id: applicationShortcutPage
                tools: backLayout
                clip: true
                orientationLock: settingsWrapper.orientation == "landscape" ?
                                     PageOrientation.LockLandscape: PageOrientation.LockPortrait

                ListView {
                    anchors.fill: parent
                    model: applicationsModel
                    delegate: LauncherClickableEntry {
                        text: model.name
                        icon: LBIFunctions.mainIcon(model.type == FolderModel.ApplicationType,
                                                    model.properties)
                        sub1Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 0)
                        sub2Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 1)
                        sub3Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 2)
                        sub4Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 3)
                        indicatorIcon: model.type == FolderModel.ApplicationType ? "" :
                                                     "icon-m-common-drilldown-arrow" +
                                                     (theme.inverted ? "-inverse" : "")
                        onClicked: {
                            if(model.type == FolderModel.ApplicationType) {
                                var object = new Object()
                                object.name = model.properties.name
                                object.icon = model.properties.icon
                                object.command = model.properties.command
                                container.addApplicationShortcut(object)
                                container.accept()
                            } else {
                                applicationShortcutSubfolderPage.model = model.properties
                                pageStack.push(applicationShortcutSubfolderPage)
                            }
                        }
                    }
                }
            }

            Page {
                id: applicationShortcutSubfolderPage
                tools: backLayout
                clip: true
                orientationLock: settingsWrapper.orientation == "landscape" ?
                                     PageOrientation.LockLandscape: PageOrientation.LockPortrait
                property variant model
                ListView {
                    anchors.fill: parent
                    model: applicationShortcutSubfolderPage.model
                    delegate: LauncherClickableEntry {
                        text: model.name
                        icon: LBIFunctions.mainIcon(model.type == FolderModel.ApplicationType,
                                                    model.properties)
                        sub1Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 0)
                        sub2Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 1)
                        sub3Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 2)
                        sub4Icon: LBIFunctions.subIcon(model.type == FolderModel.ApplicationType,
                                                       model.properties, 3)
                        indicatorIcon: ""
                        onClicked: {
                            var object = new Object()
                            object.name = model.properties.name
                            object.icon = model.properties.icon
                            object.command = model.properties.command
                            container.addApplicationShortcut(object)
                            container.accept()
                        }
                    }
                }
            }
        }

        ToolBar {
            id: toolbar
            anchors.bottom: parent.bottom
            tools: null

            ToolBarLayout {
                id: backLayout
                visible: false
                ToolIcon { iconId: "toolbar-back"; onClicked: pageStack.pop()}
            }
        }
    }
}
