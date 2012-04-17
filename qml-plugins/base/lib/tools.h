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

#ifndef WIDGETS_TOOLS_H
#define WIDGETS_TOOLS_H

namespace Widgets
{

class Tools
{
public:
    inline static bool stringToBool(const QString &value) {
        if (value == QString("true")) {
            return true;
        } else {
            return false;
        }
    }
    inline static QString boolToString(bool value) {
        if (value) {
            return QString("true");
        } else {
            return QString("false");
        }
    }
};

}

#endif // WIDGETS_TOOLS_H
