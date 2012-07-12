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

#include "componentbase.h"

#include <QtCore/QPair>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "version.h"

namespace Widgets
{

class PackageManager;
class PackagePrivate;
class Package: public ComponentBase
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QString directory READ directory NOTIFY directoryChanged)
    Q_PROPERTY(QString plugin READ plugin NOTIFY pluginChanged)
    Q_PROPERTY(QString author READ author NOTIFY authorChanged)
    Q_PROPERTY(QString email READ email NOTIFY emailChanged)
    Q_PROPERTY(QString website READ website NOTIFY websiteChanged)
    Q_PROPERTY(Version version READ version NOTIFY versionChanged)
public:
    explicit Package(QObject *parent = 0);
    virtual ~Package();
    QString identifier() const;
    QString directory() const;
    QString plugin() const;
    QString author() const;
    QString email() const;
    QString website() const;
    Version version() const;
    bool isVisible() const;
    QStringList tags() const;
    static Package * fromDesktopFile(const QString &desktopFile, QObject *parent = 0);
Q_SIGNALS:
    void identifierChanged();
    void directoryChanged();
    void pluginChanged();
    void authorChanged();
    void emailChanged();
    void websiteChanged();
    void versionChanged();
protected:
    Package(PackagePrivate *dd, QObject *parent = 0);
private:
    explicit Package(const QString &desktopFile, QObject *parent = 0);
    void setIdentifier(const QString &identifier);
    void setDirectory(const QString &directory);
    void setPlugin(const QString &plugin);
    void setAuthor(const QString &author);
    void setEmail(const QString &email);
    void setWebsite(const QString &website);
    void setVersion(const Version &version);
    void setVisible(bool isVisible);
    void setTags(const QStringList tags);
    W_DECLARE_PRIVATE(Package)
    friend class PackageManager;
};

}

#endif // WIDGETS_PACKAGE_H
