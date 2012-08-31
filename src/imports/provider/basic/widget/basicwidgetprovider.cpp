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
 * @file basicwidgetprovider.cpp
 * @short Implementation of Widgets::Provider::Basic::BasicWidgetProvider
 */

#include "basicwidgetprovider.h"
#include "widgetproviderbase_p.h"
#include "widgetbaseproperties.h"

#include <QtCore/QMap>
#include <QtCore/QDir>
#include <QtCore/QFile>

namespace Widgets
{

namespace Provider
{

namespace Basic
{

/**
 * @brief DESCRIPTION_FILENAME
 *
 * Used in Widgets::Provider::Basic::BasicWidgetProvider.
 */
static const char *DESCRIPTION_FILENAME = "widgets.txt";

/**
 * @internal
 * @brief Private class for Widgets::Provider::Basic::BasicWidgetProvider
 */
class BasicWidgetProviderPrivate: public WidgetProviderBasePrivate
{
public:
    /**
     * @internal
     * @brief Update the informations
     *
     * This method is used to update the cached informations
     * in this class. It is called when the path has changed.
     */
    void update();
    /**
     * @internal
     * @brief Path to search for widgets
     */
    QString widgetsPath;
    /**
     * @internal
     * @brief Data about widgets
     */
    QMap <QString, QString> widgetsData;
};


void BasicWidgetProviderPrivate::update()
{
    widgetsData.clear();

    QDir dir = QDir(widgetsPath);
    if (!dir.exists(DESCRIPTION_FILENAME)) {
        return;
    }

    QFile file (dir.absoluteFilePath(DESCRIPTION_FILENAME));
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList lineSplitted = line.split(";");

        if (lineSplitted.count() == 1) {
            widgetsData.insert(lineSplitted.at(0).trimmed(), QString());
        }

        if (lineSplitted.count() == 2) {
            widgetsData.insert(lineSplitted.at(0).trimmed(), lineSplitted.at(1).trimmed());
        }
    }
    file.close();
}

////// End of private class //////

BasicWidgetProvider::BasicWidgetProvider(QObject *parent):
    WidgetProviderBase(new BasicWidgetProviderPrivate(), parent)
{
    setAvailable(true);
}

BasicWidgetProvider::~BasicWidgetProvider()
{
}

QString BasicWidgetProvider::widgetsPath() const
{
    Q_D(const BasicWidgetProvider);
    return d->widgetsPath;
}

QStringList BasicWidgetProvider::registeredWidgets(const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicWidgetProvider);
    return d->widgetsData.uniqueKeys();
}

QString BasicWidgetProvider::widgetFile(const QString &fileName, const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicWidgetProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->widgetsData.contains(fileNameTrimmed)) {
        return QString();
    }

    QDir dir = QDir(widgetsPath());
    return dir.absoluteFilePath(fileNameTrimmed);
}


QString BasicWidgetProvider::widgetSettingsFile(const QString &fileName,
                                                const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicWidgetProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->widgetsData.contains(fileNameTrimmed)) {
        return QString();
    }

    QDir dir = QDir(widgetsPath());
    return dir.absoluteFilePath(d->widgetsData.value(fileNameTrimmed));
}

WidgetBaseProperties * BasicWidgetProvider::widget(const QString &fileName,
                                             const QVariantMap &disambiguation)
{
    Q_D(const BasicWidgetProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->widgetsData.contains(fileNameTrimmed)) {
        return 0;
    }

    QDir dir = QDir(widgetsPath());
    QString file = dir.absoluteFilePath(fileNameTrimmed);

    return WidgetBaseProperties::fromQmlFile(file, disambiguation,
                                             d->widgetsData.value(fileNameTrimmed), this);
}

void BasicWidgetProvider::setWidgetsPath(const QString &widgetsPath)
{
    Q_D(BasicWidgetProvider);
    if (d->widgetsPath != widgetsPath) {
        d->widgetsPath = widgetsPath;
        d->update();
        emit widgetsPathChanged();
    }
}

}

}

}
