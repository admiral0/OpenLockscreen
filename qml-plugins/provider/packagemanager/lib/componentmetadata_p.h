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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_COMPONENTMETADATA_P_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_COMPONENTMETADATA_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.


#include "desktopcomponent.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class ComponentMetadataPrivate;
class ComponentMetadata: public DesktopComponent
{
    Q_OBJECT
    Q_ENUMS(ComponentType)
    Q_PROPERTY(ComponentType type READ type CONSTANT)
    Q_PROPERTY(QString fileName READ fileName CONSTANT)
    Q_PROPERTY(QString settingsFileName READ settingsFileName CONSTANT)
public:
    enum ComponentType {
        InvalidComponentType,
        WidgetComponentType,
        DockComponentType
    };
    explicit ComponentMetadata(const QString &icon,
                               const QString &defaultName, const QString &defaultDescription,
                               const QHash<QString, QString> &names,
                               const QHash<QString, QString> &descriptions,
                               ComponentType type,
                               const QString fileName, const QString settingsFileName,
                               QObject *parent = 0);

    ComponentType type() const;
    QString fileName() const;
    QString settingsFileName() const;
    static ComponentMetadata * fromDesktopFile(const QString &desktopFile, QObject *parent = 0);
private:
    W_DECLARE_PRIVATE(ComponentMetadata)
};

}

}

}

#endif // COMPONENTMETADATA_P_H
