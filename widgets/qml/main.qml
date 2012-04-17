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
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.background 1.0
import org.SfietKonstantin.widgets.extra 1.0

PageStackWindow
{
    initialPage: mainPage

    Page {
        id: mainPage

        Settings {
            id: settings
            defaultSettings: SettingsEntry {
                key: "wallpaper/source"
                value: "/home/sk/Code/Qt/Harmattan/widgets/widgets/data/wallpaper-1.jpg"
            }
        }

        GridManager {
            id: gridManager
            settings: settings
        }

        PackageManager {
            id: packageManager
        }

        HorizontalParallaxBackground {
            id: background
            view: view
            settings: settings
        }

        ListView {
            id: view
            anchors.fill: parent
            model: ListModel {
                ListElement {
                }
                ListElement {
                }
                ListElement {
                }
                ListElement {
                }
                ListElement {
                }
                ListElement {
                }
            }
            orientation: ListView.Horizontal
            snapMode: ListView.SnapToItem
            delegate: Item {
                width: view.width
                height: view.height

                Rectangle {
                    anchors.top: parent.top
                    width: 100
                    height: 100
                }
            }

            onWidthChanged: gridManager.setViewWidth(width)
            onHeightChanged: gridManager.setViewHeight(height)
        }
    }
}
