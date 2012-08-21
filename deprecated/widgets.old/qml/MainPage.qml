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
import org.sk.widgets 1.0

// Main page
// This page contains all the components
// that are used to create the widgets
Page {
    id: mainPage

    // Each page must have an
    // orientation locking
    orientationLock: settingsWrapper.orientation == "landscape" ? PageOrientation.LockLandscape:
                                                                  PageOrientation.LockPortrait

    Item {
        id: container
        // Default scale when widgets
        // are unlocked
        property real unlockedViewScale: settingsWrapper.orientation == "portrait" ? 0.88 : 0.82

        // Precomputed widget grid
        // width and height
        property int gridWidth:(settingsWrapper.gridCellWidth +
                                settingsWrapper.gridCellHorizontalMargin) *
                                viewManager.gridWidth -
                                settingsWrapper.gridCellHorizontalMargin
        property int gridHeight:(settingsWrapper.gridCellHeight +
                                 settingsWrapper.gridCellVerticalMargin) *
                                viewManager.gridHeight -
                                settingsWrapper.gridCellVerticalMargin
        anchors.fill: parent

        Background {
            id: background
            view: view
        }

        Unlocker {
            id: unlocker
        }

        PagesView {
            id: view
            width: container.width
            height: container.height
            unlockedViewScale: container.unlockedViewScale
            gridWidth: container.gridWidth
            gridHeight: container.gridHeight
            anchors.centerIn: parent
        }

        DragManager {
            id: dragManager
            width: container.width
            height: container.height
            unlockedViewScale: container.unlockedViewScale
            gridWidth: container.gridWidth
            gridHeight: container.gridHeight

        }

    }

    DocksView {
        id: docksView
        anchors.fill: parent
    }

    Launcher {
        id: launcher
        anchors.fill: parent
    }

    MainPageToolbar {
        id: toolbars
        parent: container
        onAddWidgetClicked: widgetsSelectorSheet.open()
        onMenuClicked: menu.open()
        onHomeClicked: launcherManager.launcherVisible = false

        Connections {
            target: viewManager
            onLockedChanged: {
                if(!viewManager.locked) {
                    toolbars.setWidgetLayout()
                } else {
                    toolbars.setNullLayout()
                }
            }
        }
    }

    MainPageToolbarMenu {
        id: menu
        onEditDocksClicked: docksSelectorSheet.open()
    }

    SelectorWidgetsSheet {
        id: widgetsSelectorSheet
        visualParent: container

        onAddWidget: {
            var pageModel = displayedPagesModel.pageModel(view.currentIndex)
            var rect = viewManager.availableRect(widget.defaultWidth, widget.defaultHeight)
            if(rect.width != 0 && rect.height != 0) {
                pageModel.addWidget(widget, rect.x, rect.y, rect.width, rect.height, settings)
            } else {
                noPlaceBanner.show()
            }
        }

        onAddApplicationShortcut: {
            var widget = packageManager.widget("/opt/widgets/qml/Icon.qml")
            var pageModel = displayedPagesModel.pageModel(view.currentIndex)
            var rect = viewManager.availableRect(widget.defaultWidth, widget.defaultHeight)
            if(rect.width != 0 && rect.height != 0) {
                pageModel.addWidget(widget, rect.x, rect.y, rect.width, rect.height, shortcut)
            } else {
                noPlaceBanner.show()
            }
        }
    }

    SelectorDocksSheet {
        id: docksSelectorSheet
    }

    InfoBanner {
        id: noPlaceBanner
        text: qsTr("No place left on homescreen for this widget")
    }

    QueryDialog {
        id: welcomeDialog
        titleText: qsTr("Information")
        icon: "/usr/share/icons/hicolor/80x80/apps/widgets.png"
        acceptButtonText: qsTr("Close")
        Component.onCompleted: {
            if(settings.settingsStatus == Settings.SettingsWiped) {
                message = qsTr("Widgets has been upgraded. Old settings are now\
incompatible and has been removed. Sorry for the inconvenience.\n\n\
Current version : ") + settings.version
                open()
            }
        }
    }
}
