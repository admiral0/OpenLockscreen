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

#ifndef WIDGETS_PROVIDER_BASIC_PLUGIN_H
#define WIDGETS_PROVIDER_BASIC_PLUGIN_H

/**
 * @file widgets_provider_basic_plugin.h
 * @short Definition of Widgets::Colors::WidgetsColorsPlugin
 */

#include <QtDeclarative/QDeclarativeExtensionPlugin>

namespace Widgets
{

namespace Provider
{

namespace Basic
{

/**
 * @page pluginProviderBasic QML plugin for a basic widget provider
 *
 * @todo write this page
 */
/**
 * @internal
 * @brief QML plugin for basic widget provider
 */
class WidgetsProviderPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    /**
     * @internal
     * @brief Initialize engine
     * @param engine QML engine.
     * @param uri uri used in the import.
     */
    void initializeEngine(QDeclarativeEngine *engine, const char *uri);
    /**
     * @internal
     * @short Register types
     * @param uri uri used in the import.
     */
    void registerTypes(const char *uri);
};

}

}

}

#endif // WIDGETS_PROVIDER_BASIC_PLUGIN_H

