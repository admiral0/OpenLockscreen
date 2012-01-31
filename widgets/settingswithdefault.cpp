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

/**
 * @file settingswithdefault.cpp
 * @short Implementation of Widgets::SettingsWithDefault
 *
 * This file contains the implemetation of the
 * Widgets::SettingsWithDefault class.
 */

#include "settingswithdefault.h"
#include "dockproperties.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QStringList>

namespace Widgets
{

SettingsWithDefault::SettingsWithDefault(QObject *parent):
    Settings(parent)
{
    setDefaultSettings();
}

SettingsWithDefault::~SettingsWithDefault()
{
}

void SettingsWithDefault::setDefaultSettings()
{
    // Default settings
    setDefaultValue("view/orientation", "portrait");
    setDefaultValue("view/pageCount", 5);
    setDefaultValue("view/pageInitialIndex", 2);
    setDefaultValue("view/gridCellWidth", 110);
    setDefaultValue("view/gridCellHeight", 110);
    setDefaultValue("view/gridCellHorizontalMargin", 5);
    setDefaultValue("view/gridCellVerticalMargin", 5);

    // Default wallpaper
    if(value("wallpaper/source") == QVariant()) {
        QDir dir = QDir(QCoreApplication::instance()->applicationDirPath());
        dir.cdUp();
        dir.cd("data");

        setDefaultValue("wallpaper/source", dir.absoluteFilePath("wallpaper-1.jpg"));
        setDefaultValue("wallpaper/width", 1440);
        setDefaultValue("wallpaper/height", 900);
    }

    // Default dock
    if (value("dock/identifiers") == QVariant()) {
        QDir dir = QDir(QCoreApplication::instance()->applicationDirPath());
        dir.cdUp();
        dir.cd("widgets");

        if(dir.cd("basicwidgets")) {
            if(dir.exists("MaemoDock.qml")) {
                DockProperties *dock = new DockProperties("Maemo Dock", 480, 80,
                                                          true, false, true, false,
                                                          dir.absoluteFilePath("MaemoDock.qml"),
                                                          "basicwidgets",
                                                          false, QVariantMap());
                QVariantMap dockMap = dock->toMap();
                QStringList identifiers;
                identifiers.append(dock->identifier());

                QString dockKey = QString("dock/dock_%1").arg(dock->identifier());

                setDefaultValue("dock/identifiers", identifiers);
                setDefaultValue(dockKey, dockMap);
            }
        }
    }
}

}
