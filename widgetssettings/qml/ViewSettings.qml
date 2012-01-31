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
import "../../widgets/qml/UiConstants.js" as UI
import "../../widgets/qml"

Item {
    id: container
    anchors.fill: parent

    Item {
        id: header
        height: UI.HEADER_HEIGHT_PORTRAIT
        width: parent.width

        Label {
            id: headerLabel
            width: parent.width
            height: parent.height
            anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
            horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
            platformStyle: LabelStyle {
                fontPixelSize: UI.FONT_SIZE_XLARGE
                textColor: theme.interted ? UI.FONT_COLOR_INVERTED_PRIMARY : UI.FONT_COLOR_PRIMARY
            }
            text: qsTr("Settings")

        }

        HorizontalSeparator {
            id: headerSeparator
            anchors.top: header.bottom
        }
    }

    GroupIndicator {
        id: settingsGroupIndicatorIndicator
        anchors.top: header.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
        text: qsTr("Display")
    }

    ClickableEntry {
        id: orientationEntry
        anchors.top: settingsGroupIndicatorIndicator.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.right: parent.right
        text: qsTr("Orientation")
        subText: qsTr("Portrait")
        indicatorIcon: "icon-m-" + (theme.inverted ? "textinput" : "common") +
                       "-combobox-arrow"
//        onClicked: {
//            if(settingsWrapper.orientation == "landscape") {
//                settings.setValue("view/orientation", "portrait")
//            } else {
//                settings.setValue("view/orientation", "landscape")
//            }
//        }
    }


}
