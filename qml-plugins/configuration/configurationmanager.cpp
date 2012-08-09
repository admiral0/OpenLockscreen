/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#include "configurationmanager.h"

namespace Widgets
{

class ConfigurationManagerPrivate
{
public:
    ConfigurationManagerPrivate();
    DockProperties *currentDock;
    WidgetProperties *currentWidget;
};

ConfigurationManagerPrivate::ConfigurationManagerPrivate()
{
    currentDock = 0;
    currentWidget = 0;
}

////// End of private class //////

ConfigurationManager::ConfigurationManager(QObject *parent) :
    QObject(parent), d_ptr(new ConfigurationManagerPrivate())
{
}

ConfigurationManager::~ConfigurationManager()
{
}

DockProperties * ConfigurationManager::currentDock() const
{
    Q_D(const ConfigurationManager);
    return d->currentDock;
}

WidgetProperties * ConfigurationManager::currentWidget() const
{
    Q_D(const ConfigurationManager);
    return d->currentWidget;
}

void ConfigurationManager::setCurrentDock(DockProperties *currentDock)
{
    Q_D(ConfigurationManager);
    if (d->currentDock != currentDock) {
        d->currentDock = currentDock;
        emit currentDockChanged();
    }
}

void ConfigurationManager::setCurrentWidget(WidgetProperties *currentWidget)
{
    Q_D(ConfigurationManager);
    if (d->currentWidget != currentWidget) {
        d->currentWidget = currentWidget;
        emit currentWidgetChanged();
    }
}

void ConfigurationManager::requestSaveDockSettings()
{
    emit saveDockSettingsRequested();
}

void ConfigurationManager::requestSaveWidgetSettings()
{
    emit saveWidgetSettingsRequested();
}

void ConfigurationManager::saveDockSettings(const QVariantMap &settings)
{
    Q_D(ConfigurationManager);
    if (!d->currentDock) {
        return;
    }

    d->currentDock->setSettings(settings);
}

void ConfigurationManager::saveWidgetSettings(const QVariantMap &settings)
{
    Q_D(ConfigurationManager);
    if (!d->currentWidget) {
        return;
    }

    d->currentWidget->setSettings(settings);
}

}
