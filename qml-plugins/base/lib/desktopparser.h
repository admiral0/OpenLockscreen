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

#ifndef WIDGETS_DESKTOPPARSER_H
#define WIDGETS_DESKTOPPARSER_H

#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

namespace Widgets
{

class DesktopParserPrivate;
class DesktopParser
{
public:
    explicit DesktopParser(const QString &file);
    virtual ~DesktopParser();
    QString file() const;
    void beginGroup(const QString &group);
    void endGroup();
    QStringList keys() const;
    bool contains(const QString &key, const QString &lang = QString()) const;
    QVariant value(const QString &key, const QString &lang = QString()) const;
protected:
    DesktopParser(DesktopParserPrivate * dd);
    const QScopedPointer<DesktopParserPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DesktopParser)
};

}

#endif // WIDGETS_DESKTOPPARSER_H
