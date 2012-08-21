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

Item {
   id: container
   property QtObject gridManagerInstance: gridManager
   property alias content: contentItem.children
   property alias contentItem: contentItem
   property bool busy
   anchors.fill: parent
   Component.onCompleted: {
       gridManager.setViewWidth(width)
       gridManager.setViewHeight(height)
   }
   onWidthChanged: gridManager.setViewWidth(width)
   onHeightChanged: gridManager.setViewHeight(height)

    GridManager {
        id: gridManager
        settings: Settings {
            defaultSettings: [
                SettingsEntry {
                    group: "grid"
                    key: "cellWidth"
                    value: 100
                },
                SettingsEntry {
                    group: "grid"
                    key: "cellHeight"
                    value: 100
                },
                SettingsEntry {
                    group: "grid"
                    key: "cellHorizontalMargin"
                    value: 20
                },
                SettingsEntry {
                    group: "grid"
                    key: "cellVerticalMargin"
                    value: 20
                }
            ]
        }
    }

    Item {
        id: contentItem
        anchors.centerIn: parent
        width: gridManager.containerWidth
        height: gridManager.containerHeight
    }
}
