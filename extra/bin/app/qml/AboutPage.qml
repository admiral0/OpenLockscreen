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
import "UiConstants.js" as Ui

AbstractPage {
    id: container
    onVisibleChanged: {
        if (!visible) {
            flickable.contentY = 0
        }
    }

    title: qsTr("About")
    tools: ToolBarLayout {
        ToolIcon { iconId: "toolbar-back"; onClicked: window.pageStack.pop() }
    }
    content: Flickable {
        id: flickable
        clip: true
        anchors.fill: parent
        contentWidth: container.width
        contentHeight: Ui.MARGIN_XLARGE + icon.height + Ui.MARGIN_LARGE + aboutText.height +
                       Ui.MARGIN_DEFAULT + copyrightText.height + Ui.MARGIN_DEFAULT +
                       separator1.height + Ui.MARGIN_DEFAULT + oxygenText.height +
                       Ui.MARGIN_DEFAULT + separator2.height + Ui.MARGIN_DEFAULT +
                       artworkText.height + Ui.MARGIN_DEFAULT + separator3.height +
                       Ui.MARGIN_DEFAULT + tangoText.height + Ui.MARGIN_LARGE


        Image {
            id: icon
            width: 80; height: 80
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_XLARGE
//            source: "/usr/share/icons/hicolor/80x80/apps/widgets.png"
        }

        Label {
            id: aboutText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: icon.bottom; anchors.topMargin: Ui.MARGIN_LARGE
            wrapMode: Text.WordWrap
            text: qsTr("Widgets tries to bring you a better experience \
for your Harmattan device. Developed to be extensible and reusable, it \
provides a friendly UI, and many useful elements that informs you and made \
your phone easy to use.")
        }

        Label {
            id: copyrightText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: aboutText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            text: "(C) 2011 - Lucien XU"
        }


        HorizontalSeparator {
            id: separator1
            anchors.top: copyrightText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        }

        Label {
            id: oxygenText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: separator1.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
//            text: "Oxygen icons <br/>(Plasma and System settings)<br/>(C) The Oxygen team : \
//<a href='http://www.oxygen-icons.org'>http://www.oxygen-icons.org/</a>"
        }

        HorizontalSeparator {
            id: separator2
            anchors.top: oxygenText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        }

        Label {
            id: artworkText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: separator2.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
            text: "Wallpapers <br/>(\"Emotion\", \"Field\", \"Leafs Labyrinth\" \
and \"The Rings of Saturn\")<br/>\
(C) KDE Artwork team : <a href='http://www.kde.org'>http://www.kde.org/</a>"
        }

        HorizontalSeparator {
            id: separator3
            anchors.top: artworkText.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        }

        Label {
            id: tangoText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: separator3.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
            text: "Tango icons <br/>(Phone and Internet)<br/>The Tango team : \
<a href='http://tango.freedesktop.org/'>http://tango.freedesktop.org/</a>"
        }


    }
}
