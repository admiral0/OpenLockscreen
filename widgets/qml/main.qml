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

// Entry point for the QML program
PageStackWindow {
    id: window
    initialPage: mainPage

    // When in landscape, the status bar must be hidden
    // in order to save space
    showStatusBar: settingsWrapper.orientation == "landscape" ? false : true

    Component.onCompleted: {
        // Because inverted theme is more beautiful
        // and saves power
        theme.inverted = true

        // Toolbar on pageStack is
        // not needed
        pageStack.toolBar = null
    }

    // Testing
    // Simulating pinch / unpinch to lock / unlock
    Keys.onPressed: {
        if(event.key == Qt.Key_U) {
            viewManager.locked = false
            event.accepted = true
        } else if(event.key == Qt.Key_L) {
            viewManager.locked = true
            event.accepted = true
        }
    }

    Api {
        id: api
    }

    MainPage {
        id: mainPage
    }
}
