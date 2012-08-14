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
import org.SfietKonstantin.widgets 1.0
import org.SfietKonstantin.widgets.extra.packagemanager 1.0
import "UiConstants.js" as Ui

AbstractPage {
    id: container
    title: qsTr("Installed packages")
    tools: ToolBarLayout {
        ToolIcon { iconId: "toolbar-back"; onClicked: window.pageStack.pop() }
    }
    content: ListView {
        id: view
        anchors.fill: parent
        model: packageInformationModel
        clip: true
        delegate: ClickableEntry {
            text: model.name
            onClicked: {
                packageDetailPage.title = model.name
                packageDetailPage.description = model.description
                packageDetailPage.author = model.author
                packageDetailPage.email = model.email
                packageDetailPage.website = model.website
                packageDetailPage.version = model.version
                window.pageStack.push(packageDetailPage)
            }
        }
    }

    PackageInformationModel {
        id: packageInformationModel
        packageManager: ProviderManagerInstance.provider
    }

    PackageDetailPage {
        id: packageDetailPage
    }
}
