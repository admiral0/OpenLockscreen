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

/**
 * @file widgetproviderbase.cpp
 * @short Implementation of Widgets::WidgetProviderBase
 */

#include "widgetproviderbase.h"
#include "widgetproviderbase_p.h"

namespace Widgets
{

WidgetProviderBasePrivate::WidgetProviderBasePrivate()
{
    available = false;
}

////// End of private class //////

WidgetProviderBase::WidgetProviderBase(QObject *parent) :
    QObject(parent), d_ptr(new WidgetProviderBasePrivate())
{
}

WidgetProviderBase::WidgetProviderBase(WidgetProviderBasePrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

WidgetProviderBase::~WidgetProviderBase()
{
}

bool WidgetProviderBase::isAvailable() const
{
    Q_D(const WidgetProviderBase);
    return d->available;
}

QList<QVariantMap> WidgetProviderBase::disambiguationList() const
{
    QList<QVariantMap> values;
    values.append(QVariantMap());
    return values;
}

QStringList WidgetProviderBase::registeredWidgets(const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    return QStringList();
}

QString WidgetProviderBase::widgetFile(const QString &fileName,
                                       const QVariantMap &disambiguation) const
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return QString();
}

QString WidgetProviderBase::widgetSettingsFile(const QString &fileName,
                                               const QVariantMap &disambiguation) const
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return QString();
}

WidgetBaseProperties * WidgetProviderBase::widget(const QString &fileName,
                                                  const QVariantMap &disambiguation)
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return 0;
}

QString WidgetProviderBase::widgetName(const QString &fileName,
                                       const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation)
    return fileName;
}

QString WidgetProviderBase::widgetDescription(const QString &fileName,
                                              const QVariantMap &disambiguation) const
{
    Q_UNUSED(fileName)
    Q_UNUSED(disambiguation)
    return QString();
}

void WidgetProviderBase::setAvailable(bool available)
{
    Q_D(WidgetProviderBase);
    if (d->available != available) {
        d->available = available;
        emit availableChanged(d->available);
    }
}

}
