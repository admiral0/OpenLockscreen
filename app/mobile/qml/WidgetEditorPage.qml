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
import org.SfietKonstantin.widgets.background 1.0
import org.SfietKonstantin.widgets.docks 1.0
import org.SfietKonstantin.widgets.drag 1.0
import org.SfietKonstantin.widgets.extra 1.0
import "UiConstants.js" as Ui

Page {
    id: container
    orientationLock: PageOrientation.LockPortrait

    Component.onCompleted: {
        DragParametersInstance.removeButtonSource = "image://theme/icon-m-framework-close-thumbnail"
        DragParametersInstance.editButtonSource = "image://theme/icon-l-settings"
    }

    // The background slows down the transition
    // Therefore it is removed until a better solution is found
//    Background {
//        anchors.fill: parent
//        id: background
        // Currently disabled because of bugs in PageView
        //view: widgetsPage.view
        // initialX: widgetsPage.initialX
//    }

    EmptyDockedView {
        content: Item {
            id: widgets
            anchors.fill: parent

            WidgetsHorizontalPageView {
                id: widgetsPage
            }

            DragOverlay {
                id: dragOverlay
                onShowWidgetSettings: configureWidgetSheet.configure(widget)
                widgetsView: widgetsPage
            }
        }
    }

    Sheet {
        id: addWidgetSheet
        rejectButtonText: qsTr("Cancel")
        content: ListView {
            id: view
            anchors.fill: parent
            model: WidgetInformationModel {
                packageManager: PackageManagerInstance
            }
            clip: true
            delegate: ClickableEntry {
                text: model.name
                subText: model.description
                indicatorIcon: ""
                onClicked: {
                    var widget = PackageManagerInstance.widget(model.package, model.file)
                    WidgetsPageListModelInstance.addWidget(WidgetsPageListModelInstance.currentPage,
                                                           widget, widgetsPage.gridManagerInstance)
                    addWidgetSheet.accept()
                }
            }
        }
    }

    Sheet {
        id: configureWidgetSheet
        property Item settingsItem
        acceptButtonText: qsTr("Close")
        content: Item {
            id: contentContainer
            anchors.fill: parent
        }

        function slotSettingsChanged(settings) {
            widget.settings = settings
        }

        function configure(widget) {
            ConfigurationManagerInstance.setCurrentWidget(widget)
            var qmlFile = PackageManagerInstance.widgetSettingsFile(widget.packageIdentifier,
                                                                    widget.fileName,
                                                                    widget.settingsFileName)
            if(qmlFile != "") {
                var component = Qt.createComponent(qmlFile)
                if (component.status == Component.Ready) {
                    settingsItem = component.createObject(contentContainer ,
                                                          {"settings": widget.settings});
                } else {
                    console.debug("Cannot create the configure from file " + qmlFile +
                                  "\nerror : " + component.errorString())
//                    createDummy()
                }
                component.destroy()
            } else {
//                createDummy()
            }
            configureWidgetSheet.open()
        }
        onAccepted: {
            ConfigurationManagerInstance.requestSaveWidgetSettings()
        }

        onStatusChanged: {
            if (status == DialogStatus.Closed) {
                settingsItem.destroy()
                ConfigurationManagerInstance.setCurrentWidget(0)
            }
        }
    }

    Item {
        id: falseToolbar
        opacity: window.pageStack.busy ? 0 : 1
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 70

        ToolIcon {
            iconId: "toolbar-back"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                window.pageStack.pop()
            }
        }

        ToolButton {
            anchors.centerIn: parent
            text: qsTr("Add widget")
            onClicked: addWidgetSheet.open()
        }

        Behavior on opacity {
            NumberAnimation {duration: Ui.ANIMATION_DURATION_XFAST}
        }

        ToolIcon {
            iconId: DragManagerInstance.locked ? "toolbar-edit" : "toolbar-done"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                DragManagerInstance.locked = !DragManagerInstance.locked
            }
        }

    }
}
