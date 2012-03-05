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

.pragma library

function mainIcon(isApplication, properties) {
    if(isApplication) {
        return properties.icon
    } else {
        if(properties.count == 0) {
            return "image://theme/icon-l-folder-empty"
        } else {
            return "image://theme/icon-l-folder"
        }
    }
}

function subIcon(isApplication, properties, index) {
    if(isApplication) {
        return ""
    } else {
        if(properties.count <= index) {
            return ""
        } else {
            return properties.icon(index)
        }
    }
}
