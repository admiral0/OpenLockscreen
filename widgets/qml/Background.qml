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
import org.SfietKonstantin.widgets.background 1.0

Item {
    id: container
    anchors.fill: parent
    property Item view

    HorizontalParallaxBackground {
        view: container.view
        settings: Settings {
            defaultSettings: [
                SettingsEntry {
                    group: "background"
                    key: "wallpaperWidth"
                    value: 1440
                },
                SettingsEntry {
                    group: "background"
                    key: "wallpaperHeight"
                    value: 900
                },
                SettingsEntry {
                    group: "background"
                    key: "wallpaperSource"
                    value: "/opt/widgets/data/wallpaper-1.jpg"
                }
            ]
        }
    }
}


