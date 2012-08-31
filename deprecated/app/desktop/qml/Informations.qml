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

Page {
    id: container

    function pushChild(role) {
        if (role == "showPackageList") {
            stack.push(packageInformations)
        } else if (role == "showDockList") {
            stack.push(dockInformations)
        } else if (role == "showWidgetList") {
            stack.push(widgetInformations)
        }
    }

    ListModel {
        id: model
        ListElement {
            text: "Installed packages"
            role: "showPackageList"
        }
        ListElement {
            text: "Installed docks"
            role: "showDockList"
        }
        ListElement {
            text: "Installed widgets"
            role: "showWidgetList"
        }
    }

    ListView {
        id: view
        anchors.fill: parent
        model: model
        delegate: ClickableEntry {
            text: model.text
            onClicked: container.pushChild(model.role)
        }
    }

    Toolbar {
        id: toolbar

        IconRow {
            Icon {
                icon: "edit-undo"
                onClicked: stack.pop()
            }
        }
    }

    PackageInformations {
        id: packageInformations
    }

    DockInformations {
        id: dockInformations
    }

    WidgetInformations {
        id: widgetInformations
    }
}



