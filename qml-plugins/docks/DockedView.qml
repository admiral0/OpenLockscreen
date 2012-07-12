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
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.docks 1.0

Item {
    id: container
    anchors.fill: parent
    property alias content: contentsContainer.children

    Item {
        id: contentsContainer
        anchors.top: parent.top; anchors.topMargin: DockManagerInstance.topMargin
        anchors.bottom: parent.bottom; anchors.bottomMargin: DockManagerInstance.bottomMargin
        anchors.left: parent.left; anchors.leftMargin: DockManagerInstance.leftMargin
        anchors.right: parent.right; anchors.rightMargin: DockManagerInstance.rightMargin
    }

    Repeater {
        anchors.fill: parent
        model: DockModelInstance
        DockContainer {
            width: container.width
            height: container.height
            qmlFile: PackageManagerInstance.dockFile(model.dock.packageIdentifier,
                                                     model.dock.fileName)
        }
    }
}
