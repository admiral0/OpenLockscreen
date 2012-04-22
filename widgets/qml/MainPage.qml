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

AbstractNavigationPage {
    id: container
    orientationLock: PageOrientation.LockPortrait

    title: qsTr("Widgets settings")
    onShow: {
        if(page == "showPreview") {
            window.pageStack.push(previewPage)
        }
        if(page == "showInfo") {
            window.pageStack.push(infoPage)
        }
        if(page == "showAbout") {
            window.pageStack.push(aboutPage)
        }
    }
    model: ListModel {
        ListElement {
            identifier: "showPreview"
            text: QT_TR_NOOP("Preview")
        }

        ListElement {
            identifier: "showInfo"
            text: QT_TR_NOOP("Informations")
        }

        ListElement {
            identifier: "showAbout"
            text: QT_TR_NOOP("About")
        }
    }

    PreviewPage {
        id: previewPage
    }

    InformationsPage {
        id: infoPage
    }

    AboutPage {
        id: aboutPage
    }
}
