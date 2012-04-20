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

#include "version.h"

#include <QtCore/QRegExp>

namespace Widgets
{

static const int BETA_LIMIT = 50;

struct VersionPrivate
{
    int major;
    int minor;
    int patch;
};

////// End of private class //////

Version::Version():
    d_ptr(new VersionPrivate)
{
    Q_D(Version);
    d->major = -1;
    d->minor = -1;
    d->patch = -1;
}

Version::Version(int major, int minor, int patch):
    d_ptr(new VersionPrivate)
{
    Q_D(Version);
    if (major < 0 || minor < 0 || patch < 0) {
        d->major = -1;
        d->minor = -1;
        d->patch = -1;
        return;
    }

    d->major = major;
    d->minor = minor;
    d->patch = patch;
}

Version::Version(const Version &other):
    d_ptr(new VersionPrivate)
{
    Q_D(Version);
    d->major = other.major();
    d->minor = other.minor();
    d->patch = other.patch();
}

Version::Version(VersionPrivate *dd):
    d_ptr(dd)
{
}

Version & Version::operator=(const Version &other)
{
    Q_D(Version);
    d->major = other.major();
    d->minor = other.minor();
    d->patch = other.patch();

    return *this;
}

Version::~Version()
{
}

bool Version::operator==(const Version &other)
{
    return (major() == other.major() && minor() == other.minor() && patch() == other.patch());
}

bool Version::operator !=(const Version &other)
{
    return !(*this == other);
}

bool Version::operator >(const Version &other)
{
    if (major() > other.major()) {
        return true;
    }

    if (major() == other.major() && minor() > other.minor()) {
        return true;
    }

    return false;
}

bool Version::operator >=(const Version &other)
{
    if (major() > other.major()) {
        return true;
    }

    if (major() == other.major() && minor() >= other.minor()) {
        return true;
    }

    return false;
}

bool Version::operator <(const Version &other)
{
    if (major() < other.major()) {
        return true;
    }

    if (major() == other.major() && minor() < other.minor()) {
        return true;
    }

    return false;
}

bool Version::operator <=(const Version &other)
{
    if (major() < other.major()) {
        return true;
    }

    if (major() == other.major() && minor() <= other.minor()) {
        return true;
    }

    return false;
}

int Version::major() const
{
    Q_D(const Version);
    return d->major;
}

int Version::minor() const
{
    Q_D(const Version);
    return d->minor;
}

int Version::patch() const
{
    Q_D(const Version);
    return d->patch;
}

bool Version::isValid() const
{
    return (major() >= 0 && minor() >= 0 && patch() >= 0);
}

bool Version::isBeta() const
{
    return (minor() >= BETA_LIMIT);
}

Version Version::currentVersion()
{
    Version currentVersion (WIDGETS_VERSION_MAJOR, WIDGETS_VERSION_MINOR, WIDGETS_VERSION_PATCH);
    return currentVersion;
}

Version Version::fromString(const QString &version)
{
    QRegExp regExp ("^(\\d+)\\.(\\d+)\\.(\\d+)$");
    if (version.indexOf(regExp) == -1) {
        return Version();
    }

    int major = regExp.cap(1).toInt();
    int minor = regExp.cap(2).toInt();
    int patch = regExp.cap(3).toInt();
    return Version(major, minor, patch);
}

QString Version::toString() const
{
    return QString("%1.%2.%3").arg(major()).arg(minor()).arg(patch());
}

}
