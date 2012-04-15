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

#ifndef WIDGETS_DESKTOPPARSERPACKAGE_H
#define WIDGETS_DESKTOPPARSERPACKAGE_H

#include "desktopparserbase.h"
#include "version.h"

namespace Widgets
{

class DesktopParserPackagePrivate;
class DesktopParserPackage: private DesktopParserBase
{
public:
    DesktopParserPackage(const QString &file);
    bool isValid() const;
    QString identifier() const;
    QString name(const QString &lang) const;
    QString comment(const QString &lang) const;
    QStringList languages() const;
    QString icon() const;
    QString plugin() const;
    QString author() const;
    QString email() const;
    QString webSite() const;
    Version version() const;
private:
    Q_DECLARE_PRIVATE(DesktopParserPackage)
};

}

#endif // WIDGETS_DESKTOPPARSERPACKAGE_H
