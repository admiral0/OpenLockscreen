/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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
import "../base/" 1.0
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.provider.basic.widget 1.0

Rectangle {
    color: "black"
    width: 640
    height: 480

    // Important: settings should be passed to widgets list
    // and a provider to the provider manager
    Component.onCompleted: {
        WidgetsPageListModelInstance.settings = settings
        ProviderManagerInstance.provider = provider
    }

    // Declaration of the provider
    BasicWidgetProvider  {
        id: provider
        widgetsPath: WIDGETS_PROVIDER_FILE
    }

    // Declaration of settings
    Settings {
        id: settings
        defaultSettings: [
            SettingsEntry {
                group: "widgets"
                key: "pageCount"
                value: 1
            },
            SettingsEntry {
                group: "widgets"
                key: "initialPage"
                value: 0
            }
        ]
    }


    // An item containing the widgets horizontal page view
    Item {
        id: container
        anchors.top: parent.top; anchors.bottom: toolbar.top
        anchors.left: parent.left; anchors.right: parent.right

        WidgetsHorizontalPageView {
            id: widgetsView
            Component.onCompleted: view.interactive = false
        }
    }

    // Toolbar with buttoons
    Item {
        id: toolbar
        anchors.bottom: parent.bottom; anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        height: 40
        width: 340

        Button {
            id: add
            text: qsTr("Add widget")
            onClicked: {
                // Ask the provider for a widget
                var widget = ProviderManagerInstance.provider.widget("Dummy.qml", new Object)

                // Add the widget to the page at index 0, using
                // the grid manager that the widgets view ships
                if (!WidgetsPageListModelInstance.addWidget(0, widget,
                                                            widgetsView.gridManagerInstance)) {
                    noPlaceBanner.visible = true
                }
            }
        }

        Button {
            id: clear
            anchors.right: parent.right
            text: qsTr("Clear widgets")
            onClicked: {
                // Clear the widgets on the page at index 0
                WidgetsPageListModelInstance.clearWidgets(0)
            }
        }
    }

    Banner {
        id: noPlaceBanner
        text: qsTr("No place left")
    }
}
