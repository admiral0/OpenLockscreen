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

PageStackWindow {
    id: window
    initialPage: mainPage
    Component.onCompleted: {
        theme.inverted = true
    }

    MainPage {
        id: mainPage
        onShow: {
            if(page == "showWallpaper") {
                window.pageStack.push(backgroundSourcePage)
            }
            if(page == "showAbout") {
                window.pageStack.push(aboutPage)
            }
        }
    }

    WallpaperSourcePage {
        id: backgroundSourcePage
        onShow: {
            if(page == "showWallpaperDefault") {
                wallpaperDefaultPage.selected = settingsManager.wallpaperSource
                window.pageStack.push(wallpaperDefaultPage)
            } else if(page == "showWallpaperPictures") {
                wallpaperPicturesPage.selected = settingsManager.wallpaperSource
                window.pageStack.push(wallpaperPicturesPage)
            }
        }
    }

    WallpaperDefaultPage {
        id: wallpaperDefaultPage
    }

    WallpaperPicturesPage {
        id: wallpaperPicturesPage
    }

    AboutPage {
        id: aboutPage
    }
}
