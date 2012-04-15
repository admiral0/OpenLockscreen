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

#ifndef WIDGETS_VERSION_H
#define WIDGETS_VERSION_H

#include <QtCore/QScopedPointer>

namespace Widgets
{

class VersionPrivate;
class Version
{
public:
    Version();
    Version(int major, int minor = 0, int patch = 0);
    Version(const Version &other);
    Version &operator=(const Version &other);
    ~Version();
    bool operator==(const Version &other);
    bool operator!=(const Version &other);
    bool operator>(const Version &other);
    bool operator>=(const Version &other);
    bool operator<(const Version &other);
    bool operator<=(const Version &other);
    int major() const;
    int minor() const;
    int patch() const;
    bool isValid() const;
    bool isBeta() const;
    static Version currentVersion();
    static Version fromString(const QString &version);
    QString toString() const;
protected:
    const QScopedPointer<VersionPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(Version)
};

}

#endif // WIDGETS_VERSION_H
