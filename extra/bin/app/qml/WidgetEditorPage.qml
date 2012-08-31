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
import com.nokia.extras 1.1
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.background 1.0
import org.SfietKonstantin.widgets.docks 1.0
import org.SfietKonstantin.widgets.drag 1.0
import org.SfietKonstantin.widgets.info.widget 1.0
import "UiConstants.js" as Ui

Page {
    id: container
    orientationLock: PageOrientation.LockPortrait
    function updateBackground() {
        background.update()
    }

    onVisibleChanged: {
        if (!visible) {
            widgetsView.resetPosition()
            DragManagerInstance.locked = true
        }
    }

    Component.onCompleted: {
        DragParametersInstance.removeButtonSource = "image://theme/icon-m-framework-close-thumbnail"
        DragParametersInstance.editButtonSource = "image://theme/icon-l-settings"
    }

    Background {
        id: background
        anchors.fill: parent
        horizontalPageView: widgetsView
    }

    EmptyDockedView {
        content: Item {
            id: widgets
            anchors.fill: parent

            WidgetsHorizontalPageView {
                id: widgetsView
            }

            DragOverlay {
                id: dragOverlay
                onShowWidgetSettings: configureWidgetSheet.configure(widget)
                widgetsView: widgetsView
            }
        }
    }

    WidgetEditorSelectorSheet {
        id: addWidgetSheet
        onFailed: noPlaceBanner.show()
    }


    Sheet {
        id: configureWidgetSheet
        property Item settingsItem
        property variant widget
        acceptButtonText: qsTr("Save")
        rejectButtonText: qsTr("cancel")
        content: Item {
            id: contentContainer
            anchors.fill: parent
        }

        function slotSettingsChanged(settings) {
            widget.settings = settings
        }

        function configure(widget) {
            configureWidgetSheet.widget = widget
            var provider = ProviderManagerInstance.provider
            var qmlFile = provider.widgetSettingsFile(widget.fileName, widget.disambiguation)
            if(qmlFile != "") {
                var component = Qt.createComponent(qmlFile)
                if (component.status == Component.Ready) {
                    settingsItem = component.createObject(contentContainer ,
                                                          {"settings": widget.settings});
                } else {
                    console.debug("Cannot create the configure from file " + qmlFile +
                                  "\nerror : " + component.errorString())
                    createDummy()
                }
                component.destroy()
            } else {
                createDummy()
            }
            configureWidgetSheet.open()
        }

        function createDummy() {
            content = Qt.createQmlObject('import QtQuick 1.0;' +
                'Rectangle {color: "red"; width: ' + contentContainer.width +
                '; height: ' + contentContainer.height+ '}', contentContainer)
        }

        onAccepted: {
            WidgetConfigurationHelperInstance.requestSaveSettings(configureWidgetSheet.widget)
        }

        onStatusChanged: {
            if (status == DialogStatus.Closed) {
                if (settingsItem != null) {
                    settingsItem.destroy()
                    configureWidgetSheet.widget = 0
                }
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
                remoteSettingsManager.reloadWidgets()
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
            enabled: ProviderManagerInstance.providerStatus == ProviderManager.ProviderAvailable
        }

    }

    InfoBanner {
        id: noPlaceBanner
        text: qsTr("No place left on this page")
    }
}
