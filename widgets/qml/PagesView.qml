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
import "UiConstants.js" as UI


// Pages that contains widgets
// This is the view associated to
// the different pages that are
// used to display widgets
ListView {
    id: view
    property real unlockedViewScale
    property int gridWidth
    property int gridHeight
    anchors.fill: parent

    // When size change, we need to replace
    // the page at the initial index since
    // all the resize are during the initialization
    // phase, and may change the initial page
    onWidthChanged: {
        viewManager.setViewWidth(width)
        positionViewAtIndex(settingsWrapper.pageInitialIndex, ListView.Center)
        view.currentIndex = settingsWrapper.pageInitialIndex
    }
    onHeightChanged: {
        viewManager.setViewHeight(height)
        positionViewAtIndex(settingsWrapper.pageInitialIndex, ListView.Center)
        view.currentIndex = settingsWrapper.pageInitialIndex
    }
    interactive: viewManager.locked
    orientation: ListView.Horizontal
    highlightRangeMode: ListView.StrictlyEnforceRange
    highlightFollowsCurrentItem: true
    snapMode: ListView.SnapOneItem
    model: displayedPagesModel
    onCurrentIndexChanged: viewManager.currentPageIndex = currentIndex
    cacheBuffer: model.count * view.width

    delegate: PageWidgetsView {
        width: view.width
        height: view.height
        gridWidth: container.gridWidth
        gridHeight: container.gridHeight
        unlockedViewScale: container.unlockedViewScale
        pageModel: model.pageModel
    }

    // Move the view centered to the initial index
    // And set the initial page index
    Component.onCompleted: {
        positionViewAtIndex(settingsWrapper.pageInitialIndex, ListView.Center)
        view.currentIndex = settingsWrapper.pageInitialIndex
    }

    // If the widgets are unlocked when moving the view,
    // then we have to center the view on the current item
    Connections {
        target: viewManager
        onLockedChanged: {
            view.contentX = (view.currentIndex - settingsWrapper.pageInitialIndex) * view.width
        }
    }

    Behavior on contentX {
        NumberAnimation { duration: UI.ANIMATION_DURATION_FAST; easing.type: Easing.OutBack}
    }
}
