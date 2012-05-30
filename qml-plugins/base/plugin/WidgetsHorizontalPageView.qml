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
    property int initialX: 0

    content: Item {
        anchors.fill: parent
        ListView {
            id: view
            property bool moved: false
            function recomputeInitialX() {
                container.initialX = view.contentX -
                                     container.width * WidgetsPageListModelInstance.initialPage
            }
            orientation: ListView.Horizontal
            anchors.fill: parent
            spacing: widgets.width - view.width
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            onMovingChanged: if (moving) {moved = true}
            onWidthChanged: if (!moving) {recomputeInitialX()}
            onHeightChanged: if (!moving) {recomputeInitialX()}
            onCurrentIndexChanged: WidgetsPageListModelInstance.currentPage = currentIndex
            delegate: Item {
                width: view.width
                height: view.height

                WidgestPage {
                    anchors.fill: parent
                    pageModel: model.pageModel
                }
            }
            model: WidgetsPageListModelInstance
            Connections {
                target: WidgetsPageListModelInstance
                onInitialPageChanged: {
                    if (page != -1) {
                        view.positionViewAtIndex(page, ListView.Contain)
                        view.recomputeInitialX()
                    }
                }
            }
        }
    }
}
