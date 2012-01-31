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

AbstractPage {
    id: container
    title: qsTr("About")
    content: Flickable {
        clip: true
        anchors.fill: parent
        contentWidth: container.width
        contentHeight: UI.MARGIN_XLARGE + icon.height + UI.MARGIN_LARGE + aboutText.height +
                       UI.MARGIN_DEFAULT + copyrightText.height + UI.MARGIN_DEFAULT +
                       separator1.height + UI.MARGIN_DEFAULT + oxygenText.height +
                       UI.MARGIN_DEFAULT + separator2.height + UI.MARGIN_DEFAULT +
                       artworkText.height + UI.MARGIN_DEFAULT + separator3.height +
                       UI.MARGIN_DEFAULT + tangoText.height


        Image {
            id: icon
            width: 80; height: 80
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top; anchors.topMargin: UI.MARGIN_XLARGE
            source: "/usr/share/icons/hicolor/80x80/apps/widgets.png"
        }

        Label {
            id: aboutText
            anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
            anchors.top: icon.bottom; anchors.topMargin: UI.MARGIN_LARGE
            wrapMode: Text.WordWrap
            text: qsTr("Widgets is an application that tries to implement a\
widget system that is simple and enjoyable to use. It also tries to be\
adaptative and tries to mimic some well-known interfaces.")
        }

        Label {
            id: copyrightText
            anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
            anchors.top: aboutText.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            text: "(C) 2011 - Lucien XU"
        }


        HorizontalSeparator {
            id: separator1
            anchors.top: copyrightText.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
        }

        Label {
            id: oxygenText
            anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
            anchors.top: separator1.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
            text: "Oxygen icons <br/>(Plasma and System settings)<br/>(C) The Oxygen team : \
<a href='http://www.oxygen-icons.org'>http://www.oxygen-icons.org/</a>"
        }

        HorizontalSeparator {
            id: separator2
            anchors.top: oxygenText.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
        }

        Label {
            id: artworkText
            anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
            anchors.top: separator2.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
            text: "Wallpapers <br/>(\"Emotion\", \"Field\", \"Leafs Labyrinth\" \
and \"The Rings of Saturn\")<br/>\
(C) KDE Artwork team : <a href='http://www.kde.org'>http://www.kde.org/</a>"
        }

        HorizontalSeparator {
            id: separator3
            anchors.top: artworkText.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
        }

        Label {
            id: tangoText
            anchors.left: parent.left; anchors.leftMargin: UI.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: UI.MARGIN_DEFAULT
            anchors.top: separator3.bottom; anchors.topMargin: UI.MARGIN_DEFAULT
            wrapMode: Text.WordWrap
            textFormat: Text.RichText
            text: "Tango icons <br/>(Phone and Internet)<br/>The Tango team : \
<a href='http://tango.freedesktop.org/'>http://tango.freedesktop.org/</a>"
        }


    }
    tools: ToolBarLayout {
        ToolIcon { iconId: "toolbar-back"; onClicked: window.pageStack.pop()}
    }
}
