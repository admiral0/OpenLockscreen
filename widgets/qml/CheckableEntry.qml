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
import "UiConstants.js" as UI

// A checkable entry
// This is a ckeckable entry that can be used in a menu
// It has a checkbox, as well as an indicator.
// The indicator can be clicked too and may have a different
// behaviour than checking the box
Item {
    id: container
    property alias checked: checkBox.checked
    signal clicked(bool checked)
    property alias text: mainText.text
    property string indicatorIcon: "icon-m-common-drilldown-arrow" +
                                   (theme.inverted ? "-inverse" : "")

    height: UI.LIST_ITEM_HEIGHT_DEFAULT
    width: parent.width

    onCheckedChanged: checkBox.checked = checked

    BorderImage {
        id: background
        anchors.fill: parent
        visible: checkableMouseArea.pressed || settingsMouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    CheckBox {
        id: checkBox
        anchors.left: parent.left;
        anchors.leftMargin: UI.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        onClicked: {
            container.clicked(checked)
        }
    }

        Label {
            id: mainText
            anchors.left: checkBox.right; anchors.leftMargin: UI.MARGIN_DEFAULT
            anchors.right: indicator.left; anchors.rightMargin: UI.MARGIN_DEFAULT
            height: container.height
            verticalAlignment: Text.AlignVCenter
            platformStyle: LabelStyle {
                fontPixelSize: UI.FONT_SIZE_MLARGE
            }
        }

    Image
    {
        id: indicator
        source: container.indicatorIcon != "" ? "image://theme/" + container.indicatorIcon : ""
        anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea {
        id: checkableMouseArea
        anchors.top: container.top; anchors.bottom: container.bottom
        anchors.left: container.left
        anchors.right: indicator.left; anchors.rightMargin: UI.MARGIN_DEFAULT
        onClicked: {
            checkBox.checked = !checkBox.checked
            container.clicked(checkBox.checked)
        }
    }

    MouseArea {
        id: settingsMouseArea
        anchors.top: container.top; anchors.bottom: container.bottom
        anchors.left: checkableMouseArea.right
        anchors.right: container.right
        onClicked: {

        }
    }
}
