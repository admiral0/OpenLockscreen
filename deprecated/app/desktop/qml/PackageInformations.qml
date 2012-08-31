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
import org.SfietKonstantin.widgets.extra 1.0

Page {
    id: container

    ListView {
        id: view
        anchors.fill: parent
        model: packageInformationModel
        delegate: ClickableEntry {
            text: model.name
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

    PackageInformationModel {
        id: packageInformationModel
        packageManager: PackageManagerInstance
    }
}


