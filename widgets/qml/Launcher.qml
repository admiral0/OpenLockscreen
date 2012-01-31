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

// Application launcher
// This application launcher is nearly
// a copy of the Harmattan application
// launcher.
// It features folders as well as
// an animation when opened or closed
Item  {
    id: container
    opacity: 0
    scale: 2
    property int launcherWidth: UI.APPLICATION_LAUNCHER_WIDTH + 2 * UI.MARGIN_XSMALL
    property int launcherHeight: UI.APPLICATION_LAUNCHER_HEIGHT + 2 * UI.MARGIN_MLARGE

    Rectangle {
        id: background
        anchors.fill: parent
        opacity: 0.8
        color: colors.gray6
    }

    Item {
        id: launcherContainer
        anchors.left: container.left; anchors.leftMargin: UI.MARGIN_XSMALL
        anchors.right: container.right; anchors.rightMargin: UI.MARGIN_XSMALL
        anchors.top: container.top; anchors.topMargin: UI.MARGIN_XSMALL
        anchors.bottom: toolbar.top; anchors.bottomMargin: UI.MARGIN_LARGE

        LauncherGrid {
            id: view
            property int oldContentY

            // Open a folder
            // This function is used to compute
            // all parameters that are used to place
            // the view as well as the folder display
            function openFolder(index, subfolderName, subfolderModel) {
                openedFolderIndex = index
                var position = cellHeight * Math.ceil((index + 1)/ 4)
                var subMenuHeight = Math.min(container.launcherHeight *
                                             Math.ceil(subfolderModel.count / 4) +
                                             UI.FONT_SIZE_LARGE + 2 * UI.MARGIN_DEFAULT,
                                             view.height - UI.SUBFOLDER_BOTTOM_MARGIN)
                var subMenuY = Math.min(position - contentY - container.launcherHeight +
                                        UI.ICON_SIZE_XLARGE + UI.MARGIN_MLARGE,
                                        view.height - subMenuHeight - UI.SUBFOLDER_BOTTOM_MARGIN)

                if(position - (contentY + container.launcherHeight) < 0) {
                    contentY = position - container.launcherHeight
                }

                if(position - contentY + subMenuHeight + UI.SUBFOLDER_BOTTOM_MARGIN -
                        view.height - container.launcherHeight + UI.ICON_SIZE_XLARGE +
                        UI.MARGIN_MLARGE > 0) {
                    oldContentY = contentY
                    contentY = position + subMenuHeight + UI.SUBFOLDER_BOTTOM_MARGIN -
                            view.height - container.launcherHeight + UI.ICON_SIZE_XLARGE +
                            UI.MARGIN_MLARGE
                }

                subfolderLabel.text = subfolderName
                subfolderGrid.model = subfolderModel

                oldContentY = contentY
                interactive = false
                subfolderView.height = subMenuHeight
                subfolderView.y = subMenuY
            }

            // Close folder
            // This function is used to close a folder
            // and restore previous positions
            function closeFolder() {
                openedFolderIndex = -1
                contentY = oldContentY
                oldContentY = 0
                interactive = true
                subfolderView.height = 0
            }

            model: applicationsModel
            cellWidth:container.launcherWidth
            cellHeight:container.launcherHeight
            onClicked: {
                if(view.openedFolderIndex == -1) {
                    if(type == FolderModel.ApplicationType) {
                        launcherManager.launchApplication(properties.command)
                        launcherManager.launcherVisible = false
                    } else {
                        view.openFolder(index, name, properties)
                    }
                } else if(view.openedFolderIndex == index) {
                    view.closeFolder()
                }
            }
        }

        MouseArea {
            anchors.top: parent.top; anchors.bottom: subfolderView.top
            anchors.left: parent.left; anchors.right: parent.right
            enabled: view.openedFolderIndex != -1
            onClicked: view.closeFolder()
        }

        Rectangle {
            id: subfolderView
            height: 0
            width: container.width
            anchors.horizontalCenter: parent.horizontalCenter
            color: colors.black
            clip: true

            Label {
                id: subfolderLabel
                anchors.top: parent.top; anchors.topMargin: UI.MARGIN_DEFAULT
                anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
                anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
                font.pixelSize: UI.FONT_SIZE_DEFAULT
            }

            Item {
                id: subfolderGridContainer
                anchors.top: subfolderLabel.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
                anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_XSMALL
                anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_XSMALL

                LauncherGrid {
                    id: subfolderGrid
                    cellWidth: container.launcherWidth
                    cellHeight: container.launcherHeight
                    onClicked: {
                        if(type == FolderModel.ApplicationType) {
                            launcherManager.launchApplication(properties.command)
                            launcherManager.launcherVisible = false
                        }
                    }
                }
            }

            Behavior on height {
                NumberAnimation { duration: UI.ANIMATION_DURATION_FAST }
            }
        }

        MouseArea {
            anchors.top: subfolderView.bottom; anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.right: parent.right
            enabled: view.openedFolderIndex != -1
            onClicked: view.closeFolder()
        }
    }


    ToolBar {
        id: toolbar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            ToolIcon {
                anchors.centerIn: parent
                iconId: "toolbar-home"
                onClicked: launcherManager.launcherVisible = false
            }
        }
    }

    states: State {
        name: "visible"; when: launcherManager.launcherVisible
        PropertyChanges {
            target: container
            opacity: 1
        }
        PropertyChanges {
            target: container
            scale: 1
        }
    }

    Behavior on opacity {
        NumberAnimation { duration: UI.ANIMATION_DURATION_FAST }
    }

    Behavior on scale {
        NumberAnimation { duration: UI.ANIMATION_DURATION_FAST; easing.type: Easing.OutQuad }
    }
}
