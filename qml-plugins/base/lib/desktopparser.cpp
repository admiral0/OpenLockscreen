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

#include "desktopparser.h"

#include <QtCore/QDebug>
#include <QtCore/QSettings>

namespace Widgets
{

class DesktopParserPrivate
{
public:
    DesktopParserPrivate(const QString &file);
    static QString trueKey(const QString &key, const QString &lang);

    QString file;
    QSettings settings;
};

DesktopParserPrivate::DesktopParserPrivate(const QString &file):
    settings(file, QSettings::IniFormat)
{
    settings.setIniCodec("UTF-8");
    this->file = file;
}

QString DesktopParserPrivate::trueKey(const QString &key, const QString &lang)
{
    if (lang.isEmpty()) {
        return key;
    } else {
        QString trueKey = QString("%1[%2]").arg(key).arg(lang);
        return trueKey;
    }
}

////// End of private class //////

DesktopParser::DesktopParser(const QString &file):
    d_ptr(new DesktopParserPrivate(file))
{
}

DesktopParser::DesktopParser(DesktopParserPrivate *dd):
    d_ptr(dd)
{
}

DesktopParser::~DesktopParser()
{
}

QString DesktopParser::file() const
{
    Q_D(const DesktopParser);
    return d->file;
}

void DesktopParser::beginGroup(const QString &group)
{
    Q_D(DesktopParser);
    d->settings.beginGroup(group);
}

void DesktopParser::endGroup()
{
    Q_D(DesktopParser);
    d->settings.endGroup();
}

QStringList DesktopParser::keys() const
{
    Q_D(const DesktopParser);
    return d->settings.childKeys();
}

bool DesktopParser::contains(const QString &key, const QString &lang) const
{
    Q_D(const DesktopParser);
    return d->settings.contains(d->trueKey(key, lang));
}

QVariant DesktopParser::value(const QString &key, const QString &lang) const
{
    Q_D(const DesktopParser);
    return d->settings.value(d->trueKey(key, lang));
}

}
