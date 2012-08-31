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
import org.SfietKonstantin.widgets.info.widget 1.0
import org.SfietKonstantin.mobile.launcher 1.0
import "UiConstants.js" as Ui

Sheet {
    id: sheet
    signal failed()
    rejectButtonText: qsTr("Cancel")
    onStatusChanged: {
        if (sheet.status == DialogStatus.Closed) {
            widgetsList.positionViewAtBeginning()
            shortcutList.positionViewAtBeginning()
            shortcutSubfolderList.positionViewAtBeginning()
        }
    }
    onRejected: pageStack.pop(null)
    function addWidget(file, disambiguation) {
        var widget = ProviderManagerInstance.provider.widget(file, disambiguation)
        if (!WidgetsPageListModelInstance.addWidget(WidgetsPageListModelInstance.currentPage,
                                                    widget, widgetsView.gridManagerInstance)) {
            sheet.failed()
        }

        pageStack.pop(null)
        sheet.accept()
    }

    function addIcon(properties) {
        var settings = new Object
        settings.name = properties.name
        settings.icon = properties.icon
        settings.command = properties.command

        var disambiguation = new Object
        disambiguation.identifier = "org.SfietKonstantin.corewidgets"

        var widget = ProviderManagerInstance.provider.widget("Icon.qml", disambiguation)
        if (WidgetsPageListModelInstance.addWidget(WidgetsPageListModelInstance.currentPage,
                                                   widget, widgetsView.gridManagerInstance,
                                                   settings)) {
            sheet.failed()
        }

        pageStack.pop(null)
        sheet.accept()
    }

    content: PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: pageStack.push(mainPage)
        toolBar: toolBar
        Page {
            id: mainPage
            tools: null
            clip: true
            orientationLock: PageOrientation.LockPortrait


            ListView {
                anchors.fill: parent
                model: ListModel {
                    ListElement {
                        identifier: "addWidget"
                        text: QT_TR_NOOP("Add widget")
                    }

                    ListElement {
                        identifier: "addShortcut"
                        text: QT_TR_NOOP("Add shortcut")
                    }
                }
                delegate: ClickableEntry {
                    text: qsTranslate("", model.text)
                    onClicked: {
                        if(model.identifier == "addWidget") {
                            pageStack.push(widgetPage)
                        } else if(model.identifier == "addShortcut") {
                            pageStack.push(shortcutPage)
                        }
                    }
                }
            }
        }

        Page {
            id: widgetPage
            tools: backLayout
            clip: true
            orientationLock: PageOrientation.LockPortrait

            ListView {
                id: widgetsList
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Ui.MARGIN_DEFAULT + toolBar.height
                anchors.left: parent.left; anchors.right: parent.right
                model: WidgetInformationModel {
                    providerManager: ProviderManagerInstance
                }
                delegate: ClickableEntry {
                    text: model.name
                    subText: model.description
                    indicatorIcon: ""
                    onClicked: {
                        sheet.addWidget(model.file, model.disambiguation)
                    }
                }
            }
        }

        Page {
            id: shortcutPage
            tools: backLayout
            clip: true
            orientationLock: PageOrientation.LockPortrait

            ListView {
                id: shortcutList
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Ui.MARGIN_DEFAULT + toolBar.height
                anchors.left: parent.left; anchors.right: parent.right
                model: ApplicationsModelInstance
                delegate: ClickableEntry {
                    text: model.name
                    icon: model.type == FolderModel.ApplicationType ? model.properties.icon : ""
                    indicatorIcon: model.type == FolderModel.FolderType
                                   ? "icon-m-common-drilldown-arrow"
                                     + (theme.inverted ? "-inverse" : "")
                                   : ""
                    onClicked: {
                        if (model.type == FolderModel.ApplicationType) {
                            sheet.addIcon(model.properties)
                        } else {
                            shortcutSubfolderPage.model = model.properties
                            pageStack.push(shortcutSubfolderPage)
                        }
                    }
                }
            }
        }

        Page {
            id: shortcutSubfolderPage
            tools: backLayout
            clip: true
            orientationLock: PageOrientation.LockPortrait
            property variant model
            ListView {
                id: shortcutSubfolderList
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Ui.MARGIN_DEFAULT + toolBar.height
                anchors.left: parent.left; anchors.right: parent.right
                model: shortcutSubfolderPage.model
                delegate: ClickableEntry {
                    text: model.name
                    icon: model.type == FolderModel.ApplicationType ? model.properties.icon : ""
                    indicatorIcon: ""
                    onClicked: {
                        sheet.addIcon(model.properties)
                    }
                }
            }
        }

        ToolBar {
            id: toolBar
            anchors.bottom: parent.bottom
            tools: null
            z: 2

            ToolBarLayout {
                id: backLayout
                visible: false
                ToolIcon { iconId: "toolbar-back"; onClicked: pageStack.pop()}
            }
        }
    }

}
