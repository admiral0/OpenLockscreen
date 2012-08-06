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

Item {
    id: container
    property variant pageModel

    Repeater {
        model: container.pageModel
        delegate: WidgetContainer {
            x: model.widget.x
            y: model.widget.y
            width: model.widget.width
            height: model.widget.height
            scale: 0
            qmlFile: PackageManagerInstance.widgetFile(model.widget.packageIdentifier,
                                                       model.widget.fileName)
            visible: model.widget.visible

            Component.onCompleted: scale = 1
            Behavior on scale {
                NumberAnimation {duration: 1000; easing.type: Easing.OutBack}
            }
        }

    }
}
