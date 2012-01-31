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
import org.sk.widgets 1.0
import "../../widgets/qml/UiConstants.js" as UI

Page {
    id: container
    property string title
    property alias content: content.children

    Item {
        id: header
        anchors.top: parent.top
        anchors.left: parent.left; anchors.right: parent.right
        height: window.inPortrait ? UI.HEADER_HEIGHT_PORTRAIT : UI.HEADER_HEIGHT_LANDSCAPE

        Label {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
            verticalAlignment: Text.AlignVCenter
            text: title
            font.pixelSize: UI.FONT_SIZE_XLARGE
        }
    }

    HorizontalSeparator {
        id: horizontalSeparator
        anchors.top: header.bottom
    }

    Item {
        id: content
        anchors.top: horizontalSeparator.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
