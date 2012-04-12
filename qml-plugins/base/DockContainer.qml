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

// Dock container
// This component is used to create
// docks from QML file and to
// do the connections between
// created docks and the view
Item {
    id: container
    property Item content
    property variant dockProperties
    property string qmlFile: dockProperties.qmlFile

    // Check if the dock is valid
    // This function checks if the dock is valid
    // based on the provided anchoring and size
    // parameters.
    function isValid() {
        if((dockProperties.width == -1 &&
            (!dockProperties.anchorsLeft || !dockProperties.anchorsRight)) ||
           (dockProperties.height == -1 &&
            (!dockProperties.anchorsTop || !dockProperties.anchorsBottom))) {
            return false
        }
        return true
    }

    // Load content
    // This function is used to create
    // the widget based on a QML file
    function loadContent() {
        if(qmlFile != "") {
            var component = Qt.createComponent(qmlFile)
            if (component.status == Component.Ready) {
                content = component.createObject(container ,
                                                 {"enabled": true});
                if(dockProperties.anchorsTop) {
                    content.anchors.top = container.top
                }
                if(dockProperties.anchorsBottom) {
                    content.anchors.bottom = container.bottom
                }
                if(dockProperties.anchorsLeft) {
                    content.anchors.left = container.left
                }
                if(dockProperties.anchorsRight) {
                    content.anchors.right = container.right
                }

                if(dockProperties.width != -1 &&
                        (!dockProperties.leftMargin || !dockProperties.rightMargin)) {
                    content.width = dockProperties.width
                }
                if(dockProperties.height != -1 &&
                        (!dockProperties.topMargin || !dockProperties.bottomMargin)) {
                    content.height = dockProperties.height
                }

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
    // This function is used to create a dummy dock
    // that indicates that the dock is malfunctioning
    function createDummy() {
        content = Qt.createQmlObject('import QtQuick 1.0;' +
            'Rectangle {color: "red"; width: ' + container.width +
            '; height: ' + container.height+ '}', container)
    }

    opacity: 1

    Component.onCompleted: {
        if(isValid()) {
            loadContent()
        } else {
            createDummy()
        }
    }

    Component.onDestruction: {
        if(content != null) {
            content.destroy()
        }
    }
}
