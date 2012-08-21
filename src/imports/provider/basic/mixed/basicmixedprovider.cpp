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
 * @file basicmixedprovider.cpp
 * @short Implementation of Widgets::Provider::Basic::BasicMixedProvider
 */

#include "basicmixedprovider.h"
#include "widgetproviderbase_p.h"

#include "widgetbaseproperties.h"
#include "dockbaseproperties.h"

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
 * Used in Widgets::Provider::Basic::BasicMixedProvider.
 */
static const char *WIDGETS_DESCRIPTION_FILENAME = "widgets.txt";
/**
 * @brief DESCRIPTION_FILENAME
 *
 * Used in Widgets::Provider::Basic::BasicMixedProvider.
 */
static const char *DOCKS_DESCRIPTION_FILENAME = "docks.txt";

/**
 * @internal
 * @brief Private class for Widgets::Provider::Basic::BasicMixedProvider
 */
class BasicMixedProviderPrivate: public WidgetProviderBasePrivate
{
public:
    /**
     * @internal
     * @brief Update widgets informations
     */
    void updateWidgets();
    /**
     * @internal
     * @brief Update docks informations
     */
    void updateDocks();
    /**
     * @internal
     * @brief Helper method for updates
     *
     * This helper method perform the cache update
     * using the absolute path to the file to parse,
     * and the cache data to modify.
     *
     * @param path absolute path to the file to parse.
     * @param data cached data.
     */
    void update(const QString &path, QMap <QString, QString> *data);
    /**
     * @internal
     * @brief Path to search for widgets
     */
    QString widgetsPath;
    /**
     * @internal
     * @brief Path to search for docks
     */
    QString docksPath;
    /**
     * @internal
     * @brief Data about widgets
     */
    QMap <QString, QString> widgetsData;
    /**
     * @internal
     * @brief Data about docks
     */
    QMap <QString, QString> docksData;
};

void BasicMixedProviderPrivate::updateWidgets()
{
    QDir dir = QDir(widgetsPath);
    if (!dir.exists(WIDGETS_DESCRIPTION_FILENAME)) {
        return;
    }

    update(dir.absoluteFilePath(WIDGETS_DESCRIPTION_FILENAME), &widgetsData);
}

void BasicMixedProviderPrivate::updateDocks()
{
    QDir dir = QDir(docksPath);
    if (!dir.exists(DOCKS_DESCRIPTION_FILENAME)) {
        return;
    }

    update(dir.absoluteFilePath(DOCKS_DESCRIPTION_FILENAME), &docksData);

}

void BasicMixedProviderPrivate::update(const QString &path, QMap <QString, QString> *data)
{
    data->clear();

    QFile file (path);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList lineSplitted = line.split(";");

        if (lineSplitted.count() == 1) {
            data->insert(lineSplitted.at(0).trimmed(), QString());
        }

        if (lineSplitted.count() == 2) {
            data->insert(lineSplitted.at(0).trimmed(), lineSplitted.at(1).trimmed());
        }
    }
    file.close();
}

////// End of private class //////

BasicMixedProvider::BasicMixedProvider(QObject *parent):
    Docks::MixedProviderBase(new BasicMixedProviderPrivate(), parent)
{
    setAvailable(true);
}

BasicMixedProvider::~BasicMixedProvider()
{
}

QString BasicMixedProvider::widgetsPath() const
{
    Q_D(const BasicMixedProvider);
    return d->widgetsPath;
}

QString BasicMixedProvider::docksPath() const
{
    Q_D(const BasicMixedProvider);
    return d->docksPath;
}

QStringList BasicMixedProvider::registeredWidgets(const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicMixedProvider);
    return d->widgetsData.uniqueKeys();
}

QString BasicMixedProvider::widgetFile(const QString &fileName,
                                       const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicMixedProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->widgetsData.contains(fileNameTrimmed)) {
        return QString();
    }

    QDir dir = QDir(widgetsPath());
    return dir.absoluteFilePath(fileNameTrimmed);
}


QString BasicMixedProvider::widgetSettingsFile(const QString &fileName,
                                               const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicMixedProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->widgetsData.contains(fileNameTrimmed)) {
        return QString();
    }

    QDir dir = QDir(widgetsPath());
    return dir.absoluteFilePath(d->widgetsData.value(fileNameTrimmed));
}

WidgetBaseProperties * BasicMixedProvider::widget(const QString &fileName,
                                                  const QVariantMap &disambiguation)
{
    Q_D(const BasicMixedProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->widgetsData.contains(fileNameTrimmed)) {
        return 0;
    }

    QDir dir = QDir(widgetsPath());
    QString file = dir.absoluteFilePath(fileNameTrimmed);

    return WidgetBaseProperties::fromQmlFile(file, disambiguation,
                                             d->widgetsData.value(fileNameTrimmed), this);
}

QStringList BasicMixedProvider::registeredDocks(const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicMixedProvider);
    return d->docksData.uniqueKeys();
}

QString BasicMixedProvider::dockFile(const QString &fileName,
                                     const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicMixedProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->docksData.contains(fileNameTrimmed)) {
        return QString();
    }

    QDir dir = QDir(docksPath());
    return dir.absoluteFilePath(fileNameTrimmed);
}

QString BasicMixedProvider::dockSettingsFile(const QString &fileName,
                                             const QVariantMap &disambiguation) const
{
    Q_UNUSED(disambiguation);
    Q_D(const BasicMixedProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->docksData.contains(fileNameTrimmed)) {
        return QString();
    }

    QDir dir = QDir(docksPath());
    return dir.absoluteFilePath(d->docksData.value(fileNameTrimmed));
}

Docks::DockBaseProperties * BasicMixedProvider::dock(const QString &fileName,
                                                     const QVariantMap &disambiguation)
{

    Q_D(const BasicMixedProvider);
    QString fileNameTrimmed = fileName.trimmed();

    if (!d->docksData.contains(fileNameTrimmed)) {
        return 0;
    }

    QDir dir = QDir(docksPath());
    QString file = dir.absoluteFilePath(fileNameTrimmed);

    return Docks::DockBaseProperties::fromQmlFile(file, disambiguation,
                                                  d->docksData.value(fileNameTrimmed), this);
}

void BasicMixedProvider::setWidgetsPath(const QString &widgetsPath)
{
    Q_D(BasicMixedProvider);
    if (d->widgetsPath != widgetsPath) {
        d->widgetsPath = widgetsPath;
        d->updateWidgets();
        emit widgetsPathChanged();
    }
}

void BasicMixedProvider::setDocksPath(const QString &docksPath)
{
    Q_D(BasicMixedProvider);
    if (d->docksPath != docksPath) {
        d->docksPath = docksPath;
        d->updateDocks();
        emit docksPathChanged();
    }
}

}

}

}
