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

#include "mixedproviderbase.h"

/**
 * @file mixedproviderbase.cpp
 * @short Implementation of Widgets::Docks::MixedProviderBase
 */

namespace Widgets
{

namespace Docks
{

MixedProviderBase::MixedProviderBase(QObject *parent):
    WidgetProviderBase(parent)
{
}

MixedProviderBase::MixedProviderBase(WidgetProviderBasePrivate *dd, QObject *parent):
    WidgetProviderBase(dd, parent)
{
}

QStringList MixedProviderBase::registeredDocks(const QVariantHash &disambiguation) const
{
    Q_UNUSED(disambiguation)
    return QStringList();
}

QString MixedProviderBase::dockFile(const QString &fileName,
                                    const QVariantHash &disambiguation) const
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return QString();
}

QString MixedProviderBase::dockSettingsFile(const QString &fileName,
                                            const QVariantHash &disambiguation) const
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return QString();
}

DockBaseProperties * MixedProviderBase::dock(const QString &fileName,
                                             const QVariantHash &disambiguation)
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return 0;
}

QString MixedProviderBase::dockName(const QString &fileName,
                                    const QVariantHash &disambiguation) const
{
    Q_UNUSED(disambiguation)
    return fileName;
}

QString MixedProviderBase::dockDescription(const QString &fileName,
                                           const QVariantHash &disambiguation) const
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return QString();
}

}

}
