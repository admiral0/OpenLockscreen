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

// This item is a clickable entry
// that features an application
// icon instead of a normal icon.
Item
{
    id: container
    signal clicked
    property alias icon: icon.source
    property alias sub1Icon: icon.sub1Source
    property alias sub2Icon: icon.sub2Source
    property alias sub3Icon: icon.sub3Source
    property alias sub4Icon: icon.sub4Source
    property alias text: mainText.text
    property alias subText: subText.text
    property string indicatorIcon: "icon-m-common-drilldown-arrow" +
                                   (theme.inverted ? "-inverse" : "")

    height: UI.LIST_ITEM_HEIGHT_DEFAULT
    width: parent.width

    BorderImage
    {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    LauncherButtonIcon
    {
        id: icon
        anchors.left: parent.left;
        anchors.leftMargin: UI.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        width: UI.ICON_SIZE_LARGE
        height: UI.ICON_SIZE_LARGE
    }

    Item {
        id: textContainer
        anchors.left: icon.right; anchors.leftMargin: UI.MARGIN_DEFAULT
        anchors.right: indicator.left; anchors.rightMargin: UI.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        height: subText.text != "" ? mainText.height + UI.MARGIN_XSMALL + subText.height :
                                         mainText.height

        Label {
            id: mainText
            platformStyle: LabelStyle {
                fontPixelSize: UI.FONT_SIZE_MLARGE
            }
        }

        Label {
            id: subText
            anchors.top: mainText.bottom; anchors.topMargin: UI.MARGIN_XSMALL
            platformStyle: LabelStyle {
                fontPixelSize: UI.FONT_SIZE_SMALL
                textColor: theme.inverted ? UI.FONT_COLOR_INVERTED_SECONDARY :
                                            UI.FONT_COLOR_SECONDARY
            }
        }
    }



    Image
    {
        id: indicator
        source: container.indicatorIcon != "" ? "image://theme/" + container.indicatorIcon : ""
        anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: container
        onClicked:
        {
            container.clicked()
        }
    }
}

