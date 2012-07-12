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

#ifndef TEMPORARYPACKAGEMANAGER_H
#define TEMPORARYPACKAGEMANAGER_H

#include "../../../qml-plugins/base/plugin/packagemanager.h"

class TemporaryPackageManagerPrivate;
class TemporaryPackageManager: public Widgets::PackageManager
{
public:
    TemporaryPackageManager();
    static void deleteDb();
private:
    Q_DECLARE_PRIVATE(TemporaryPackageManager)
};

#endif // TEMPORARYPACKAGEMANAGER_H
