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

#include "desktopparserbase.h"
#include "desktopparserbase_p.h"

namespace Widgets
{

DesktopParserBase::DesktopParserBase(const QString &file):
    d_ptr(new DesktopParserBasePrivate(file))
{
}

DesktopParserBase::DesktopParserBase(DesktopParserBasePrivate *dd):
    d_ptr(dd)
{
}

DesktopParserBase::~DesktopParserBase()
{
}

void DesktopParserBase::beginGroup(const QString &group)
{
    Q_D(DesktopParserBase);
    d->settings.beginGroup(group);
}

void DesktopParserBase::endGroup()
{
    Q_D(DesktopParserBase);
    d->settings.endGroup();
}

QStringList DesktopParserBase::keys() const
{
    Q_D(const DesktopParserBase);
    return d->settings.childKeys();
}

bool DesktopParserBase::contains(const QString &key, const QString &lang) const
{
    Q_D(const DesktopParserBase);
    return d->settings.contains(d->trueKey(key, lang));
}

QVariant DesktopParserBase::value(const QString &key, const QString &lang) const
{
    Q_D(const DesktopParserBase);
    return d->settings.value(d->trueKey(key, lang));
}

}
