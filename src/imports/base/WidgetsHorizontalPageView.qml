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

WidgetsView {
    id: container
    property Item view: view
    signal initialized()
    function resetPosition() {
        view.positionViewAtIndex(WidgetsPageListModelInstance.initialPage, ListView.visible)
    }

    busy: view.moving
    clip: true

    content: Item {
        anchors.fill: parent

        EventTimer {
            id: timer
            onTriggered: {
                view.positionViewAtIndex(WidgetsPageListModelInstance.initialPage, ListView.Visible)
                container.initialized()
            }
            Component.onCompleted: start()
        }

        ListView {
            id: view
            orientation: ListView.Horizontal
            anchors.fill: parent
            spacing: container.parent.width - view.width
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            onCurrentIndexChanged: {
                WidgetsPageListModelInstance.currentPage = currentIndex
            }
            onWidthChanged: timer.start()

            // TODO : Change the hardcoded 11
            cacheBuffer: view.width * 11

            delegate: Item {
                width: view.width
                height: view.height

                WidgestPage {
                    anchors.fill: parent
                    pageModel: model.pageModel
                }
            }
            model: WidgetsPageListModelInstance
        }
    }
}
