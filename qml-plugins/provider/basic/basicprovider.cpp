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

#include "basicprovider.h"
#include "widgetbaseproperties.h"

#include <QtCore/QDir>
#include <QtCore/QFile>

namespace Widgets
{

namespace Provider
{

namespace Basic
{

static const char *DESCRIPTION_FILENAME = "widgets.txt";

class BasicProviderPrivate
{
public:
    QString path;
};

////// End of private class //////

BasicProvider::BasicProvider(QObject *parent):
    WidgetProviderBase(parent), d_ptr(new BasicProviderPrivate())
{
}

BasicProvider::~BasicProvider()
{
}

bool BasicProvider::available() const
{
    return true;
}

QString BasicProvider::path() const
{
    Q_D(const BasicProvider);
    return d->path;
}

QStringList BasicProvider::registeredWidgets(const QVariantHash &disambiguation) const
{
    Q_UNUSED(disambiguation);
    QDir dir = QDir(path());
    if (!dir.exists(DESCRIPTION_FILENAME)) {
        return QStringList();
    }

    QFile file (dir.absoluteFilePath(DESCRIPTION_FILENAME));
    if (!file.open(QIODevice::ReadOnly)) {
        return QStringList();
    }

    QStringList list;
    while (!file.atEnd()) {
        QString qmlFile = file.readLine();
        if (!qmlFile.trimmed().isEmpty()) {
            list.append(qmlFile.trimmed());
        }
    }
    file.close();


    return list;
}

QString BasicProvider::widgetFile(const QString &fileName, const QVariantHash &disambiguation) const
{
    Q_UNUSED(disambiguation);
    QDir dir = QDir(path());
    return dir.absoluteFilePath(fileName);
}


QString BasicProvider::widgetSettingsFile(const QString &fileName,
                                          const QVariantHash &disambiguation) const
{
    Q_UNUSED(fileName);
    Q_UNUSED(disambiguation);
    return QString();
}

WidgetBaseProperties * BasicProvider::widget(const QString &fileName,
                                             const QVariantHash &disambiguation)
{
    return new WidgetBaseProperties(fileName, disambiguation, "", 200, 200, 120, 200, this);
}

void BasicProvider::setPath(const QString &path)
{
    Q_D(BasicProvider);
    if (d->path != path) {
        d->path = path;
        emit pathChanged();
    }
}

}

}

}
