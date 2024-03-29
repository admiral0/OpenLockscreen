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
import "UiConstants.js" as UI

// Docks selector
// This sheet contains all the available
// docks as well as way to enable / disable
// and controlling them
Sheet {
    id: container
    rejectButtonText: qsTr("Close")
    function toggleDock(dock, enabled) {
        if(enabled) {
            displayedDocksModel.addDock(dock)
        } else {
            displayedDocksModel.removeDock(dock)
        }
    }

    content: ListView {
        anchors.fill: parent
        model: availableDocksModel
        delegate: CheckableEntry {
            checked: displayedDocksModel.hasDock(model.dock)
            onClicked: container.toggleDock(model.dock, checked)
            text: model.dock.name
            indicatorIcon: model.dock.hasSettings ? "icon-m-content-settings" +
                                                    (theme.inverted ? "-inverse" : "") : ""
        }
    }
}
