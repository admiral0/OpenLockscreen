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

#ifndef WIDGETS_EXTRA_PACKAGEMANAGER_PLUGIN_H
#define WIDGETS_EXTRA_PACKAGEMANAGER_PLUGIN_H

#include <QtDeclarative/QDeclarativeExtensionPlugin>

namespace Widgets
{

namespace Extra
{

class WidgetsExtraPackageManagerPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    /**
     * @short Register types
     *
     * This method is used to register C++ classes
     * into the QML context.
     *
     * @param uri uri used in the import.
     */
    void registerTypes(const char *uri);
};

}

}

#endif // WIDGETS_EXTRA_PACKAGEMANAGER_PLUGIN_H

