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
import org.SfietKonstantin.widgets.background 1.0

// Background with a parallax effect
Item {
    id: container
    property Item view
    property int initialX: 0
    property real parallax: 0
    property QtObject settings
    clip: true

    anchors.fill: parent

    // Update the position of the background
    // based on the current position
    // of the view
    function updateParallax() {
        if(view.model.count > 1) {
            var value = (view.contentX - container.initialX) /
                        (view.contentWidth - view.width)
            container.parallax = Math.min(Math.max(value ,0) ,1)
        } else {
            container.parallax = 0.5
        }
    }

    BackgroundManager {
        id: backgroundManager
        settings: container.settings
    }

    Rectangle {
        id: background
        height: container.height
        width: backgroundManager.wallpaperHeight != 0 ?
               backgroundManager.wallpaperWidth / backgroundManager.wallpaperHeight * height :
               0
        color: "black"
        x: - container.parallax * (background.width - container.width)

        Image {
            id: backgroundImage
            height: background.height
            width: background.width
            sourceSize.width: background.width
            anchors.centerIn: parent
            clip: true
            fillMode: Image.PreserveAspectCrop
            source: backgroundManager.wallpaperSource
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
