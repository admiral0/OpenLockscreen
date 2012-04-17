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

#ifndef WIDGETS_PACKAGE_H
#define WIDGETS_PACKAGE_H

#include <QtCore/QPair>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "version.h"

namespace Widgets
{

class PackageManager;
class PackagePrivate;
class Package
{
public:
    explicit Package();
    Package(const Package &other);
    Package & operator=(const Package &other);
    virtual ~Package();
    bool isValid() const;
    QString identifier() const;
    void setIdentifier(const QString &identifier);
    QString directory() const;
    void setDirectory(const QString &directory);
    QString defaultName() const;
    void setDefaultName(const QString &name);
    QString name() const;
    QString name(const QString &language) const;
    void addName(const QString &language, const QString &name);
    QString defaultDesription() const;
    void setDefaultDescription(const QString &description);
    QString description() const;
    QString description(const QString &language) const;
    void addDescription(const QString &language, const QString &description);
    QStringList languages() const;
    void clearNamesAndDescriptions();
    QString icon() const;
    void setIcon(const QString &icon);
    QString plugin() const;
    void setPlugin(const QString &plugin);
    QString author() const;
    void setAuthor(const QString &author);
    QString email() const;
    void setEmail(const QString &email);
    QString website() const;
    void setWebsite(const QString &website);
    Version version() const;
    void setVersion(const Version &version);
    static Package fromDesktopFile(const QString &file);
protected:
    Package(PackagePrivate * dd);
    const QScopedPointer<PackagePrivate> d_ptr;
private:
    explicit Package(const QString &file);
    QHash<QString, QPair<QString, QString> > nameAndDescription() const;
    Q_DECLARE_PRIVATE(Package)
};

}

#endif // WIDGETS_PACKAGE_H
