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

#ifndef WIDGETS_PLUGIN_H
#define WIDGETS_PLUGIN_H

/**
 * @file widgets_plugin.h
 * @short Definition of WidgetsPlugin
 *
 * This file contains the definition of the
 * WidgetsPlugin class.
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>

/**
 * @short Base QML plugin for Widgets
 *
 * This class registers all the types that are available
 * in the QML plugin for %Widgets. This plugin ships
 * all the basic components that are required to build
 * a %Widgets view.
 *
 * Declared classes and components are available in the
 * "org.SfietKonstantin.widgets 1.0" import.
 *
 * @section pluginsComponents Plugin components
 *
 *
 *
 * @todo update documentation.
 */
class WidgetsPlugin : public QDeclarativeExtensionPlugin
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

#endif // WIDGETS_PLUGIN_H

