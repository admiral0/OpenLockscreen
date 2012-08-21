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
    property Item horizontalPageView
    property QtObject settings
    property QtObject parallaxManagerInstance: parallaxManager
    clip: true

    anchors.fill: parent

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
        x: - parallaxManager.position * (background.width - container.width)

        Image {
            id: backgroundImage
            height: background.height
            width: background.width
            sourceSize.width: background.width
            anchors.centerIn: parent
            clip: true
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            source: backgroundManager.wallpaperSource
        }
    }

    ParallaxManager {
        id: parallaxManager
        contentX: horizontalPageView.view.contentX
        viewWidth: horizontalPageView.view.width
        contentWidth: horizontalPageView.view.contentWidth
    }

    Connections {
        target: horizontalPageView
        onInitialized: {
            var initialContentX =
                    horizontalPageView.view.contentX - WidgetsPageListModelInstance.currentPage
                                                       * horizontalPageView.width
            parallaxManager.initialContentX = initialContentX
        }
    }
}
