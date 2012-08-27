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
import org.SfietKonstantin.widgets.app 1.0
import "UiConstants.js" as Ui

AbstractPage {
    id: container
    property alias description: descriptionLabel.text
    property string author: ""
    property string email
    property string website
    property alias version: versionLabel.text
    function openWeb() {
        handler.openWebpage(container.website)
    }
    function openMail() {
        handler.openMailEditor(container.email)
    }

    tools: ToolBarLayout {
        ToolIcon { iconId: "toolbar-back"; onClicked: window.pageStack.pop() }
        ToolIcon {
            iconId: "toolbar-view-menu"
            visible: container.email != "" || container.website != ""
            onClicked: {
                if (container.email == "") {
                    websiteMenu.open()
                } else if (container.website == "") {
                    emailMenu.open()
                } else {
                    emailAndWebsiteMenu.open()
                }
            }
        }
    }
    content: Flickable {
        anchors.fill: parent
        contentWidth: container.width
        contentHeight: versionLabel.height + Ui.MARGIN_LARGE + descriptionLabel.height +
                       Ui.MARGIN_LARGE + authorLabel.height + Ui.MARGIN_LARGE
        clip: true

        Label {
            id: versionLabel
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        }

        Label {
            id: descriptionLabel
            anchors.top: versionLabel.bottom; anchors.topMargin: Ui.MARGIN_LARGE
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        }

        Label {
            id: authorLabel
            anchors.top: descriptionLabel.bottom; anchors.topMargin: Ui.MARGIN_LARGE
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            text: container.author == "" ? qsTr("By unknown") : qsTr("By ") + container.author
        }
    }

    Menu {
        id: emailAndWebsiteMenu
        MenuLayout {
            MenuItem {
                text: qsTr("Contact the developer")
                onClicked: container.openMail()
            }
            MenuItem {
                text: qsTr("Go to the website")
                onClicked: container.openWeb()
            }
        }
    }

    Menu {
        id: emailMenu
        MenuLayout {
            MenuItem {
                text: qsTr("Contact the developer")
                onClicked: container.openMail()
            }
        }
    }

    Menu {
        id: websiteMenu
        MenuLayout {
            MenuItem {
                text: qsTr("Go to the website")
                onClicked: container.openWeb()
            }
        }
    }

    WebAndMailHandler {
        id: handler
    }
}
