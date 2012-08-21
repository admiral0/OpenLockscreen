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

// Widget container
// This component is used to create
// widgets from QML file and to
// do the connections between
// created widgets and the view
Item {
    id: container
    property string qmlFile
    property Item content
    property color backgroundColor: "#00000000"
    property int contentWidth
    property int contentHeight
    property variant settings
    signal requireUpdateGeometry(int x, int y, int width, int height)
    signal showSettings()

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
                                                  "settings": container.settings});
                container.contentWidth = content.width
                container.contentHeight = content.height
                container.backgroundColor = content.backgroundColor
                background.visible = content.hasBackground
                container.showSettings.connect(content.showSettings)

                var size = viewManager.computeWidgetSize(content.width, content.height)
                container.requireUpdateGeometry(x, y, size.width, size.height)
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

    Rectangle {
        id: background
        anchors.fill: parent
        color: container.backgroundColor
    }

    Connections {
        target: platformWindow
        onVisibleChanged: {
            if(content != null) {
                content.enabled = platformWindow.visible
            }
        }
    }

    Connections {
        target: content.settings
        onSettingsChanged: requireUpdateGeometry(container.x, container.y,
                                                 container.width, container.height)
    }
}
