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
import org.SfietKonstantin.widgets.mobileextra 1.0
//import org.sk.widgets 1.0
import "UiConstants.js" as Ui
import "LauncherButtonIconFunctions.js" as LBIFunctions

// Launcher grid
// This grid is used to display a launcher
// or a subfolder.
GridView {
    id: container
    property int openedFolderIndex: -1
    signal clicked(string name, int type, int index, variant properties)
    anchors.fill: parent
    clip: true

    delegate: Item {
        width: container.cellWidth
        height: container.cellHeight

        LauncherButton {
            id: launcherButton
            anchors.centerIn: parent
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
            opacity: container.openedFolderIndex == -1 ? 1 :
                                                container.openedFolderIndex == model.index ? 1 : 0.2
            name: model.name
            onClicked: {
                container.clicked(model.name, model.type, model.index, model.properties)
            }

            Behavior on opacity {
                NumberAnimation { duration: Ui.ANIMATION_DURATION_FAST }
            }
        }
    }

    Behavior on contentY {
        NumberAnimation {
            duration: Ui.ANIMATION_DURATION_FAST
            easing.type: Easing.InOutQuad
        }
    }
}

