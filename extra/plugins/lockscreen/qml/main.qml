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
import org.SfietKonstantin.widgets.docks 1.0
import org.SfietKonstantin.widgets.provider.packagemanager 1.0



Rectangle {
    id: container
    anchors.fill: parent
    color: "black"
//    source: "/home/user/.wallpapers/wallpaper.png"

    Component.onCompleted: {
        WidgetsPageListModelInstance.settings = widgetsSettings
        ProviderManagerInstance.provider = provider
    }

    Settings {
        id: widgetsSettings
        defaultSettings: [
            SettingsEntry {
                group: "widgets"
                key: "pageCount"
                value: 5
            },
            SettingsEntry {
                group: "widgets"
                key: "initialPage"
                value: 2
            },
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
                value: "/opt/widgets/data/wallpaper-1.png"
            }
        ]
    }

    PackageManager {
        id: provider
        filter: packageManagerFilters
    }

    FilterConditionList {
        id: packageManagerFilters
        FilterCondition {
            tag: "mobile-harmattan"
        }
    }

    HorizontalParallaxBackground {
        id: background
        anchors.fill: parent
        settings: widgetsSettings
        horizontalPageView: widgetsPage
    }

    DockedView {
        content: Item {
            id: widgets
            anchors.fill: parent

            WidgetsHorizontalPageView {
                id: widgetsPage
            }
        }
    }

    MouseArea {
        id: unlocker
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 20
        onClicked: LockScreenManager.unlock()
    }

}

