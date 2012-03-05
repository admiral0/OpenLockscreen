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
import "UiConstants.js" as UI

// Background with a parallax effect
Item {
    id: container
    property Item view
    property real parallax: 0

    anchors.fill: parent

    // Update the position of the background
    // based on the current position
    // of the view
    function updateParallax() {
        if(view.model.count > 1) {
            var value = (view.contentX + settingsWrapper.pageInitialIndex * view.width) /
                        (view.contentWidth - view.width)
            container.parallax = Math.min(Math.max(value ,0) ,1)
        } else {
            container.parallax = 0.5
        }
    }

    Rectangle {
        id: background
        height: container.height
        width: settingsWrapper.wallpaperWidth / settingsWrapper.wallpaperHeight * height
        color: colors.skyBlue6
        x: - container.parallax * (background.width - container.width)

        Image {
            id: backgroundImage
            height: background.height
            width: background.width
            sourceSize.width: background.width
            anchors.centerIn: parent
            clip: true
            fillMode: Image.PreserveAspectCrop
            smooth: true
            source: settingsWrapper.wallpaperSource
        }
    }

    // Need to update the parallax value even if
    // the view is resizing
    Connections {
        target: view
        onContentXChanged: updateParallax()
        onWidthChanged: updateParallax()
        onHeightChanged: updateParallax()
    }
}
