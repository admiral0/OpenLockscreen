/***************************************************************************************
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
    property Item content
    property QtObject widget
    property string qmlFile

    Connections {
        target: widget
        onSettingsChanged: {
            if (content != null) {
                content.settings = widget.settings
            }
        }
    }

    // Load content
    // This function is used to create
    // the widget based on a QML file
    function loadContent() {
        if(qmlFile != "") {
            var component = Qt.createComponent(qmlFile)
            if (component.status == Component.Ready) {
                content = component.createObject(container ,
                                                 {"anchors.centerIn": container,
                                                  "enabled": true,
                                                  "settings": container.widget.settings});
            } else {
                console.debug("Cannot create the widget from file " + qmlFile +
                              "\nerror : " + component.errorString())
                createDummy()
            }
            component.destroy()
        } else {
            createDummy()
        }
    }

    // Create dummy
    // This function is used to create a dummy widget
    // that indicates that the widget is malfunctioning
    function createDummy() {
        content = Qt.createQmlObject('import QtQuick 1.0;' +
            'Rectangle {color: "red"; width: ' + container.width +
            '; height: ' + container.height+ '}', container)
    }

    Component.onCompleted: loadContent()

    Component.onDestruction: {
        if(content != null) {
            content.destroy()
        }
    }
}
