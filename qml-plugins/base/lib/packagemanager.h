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

#ifndef WIDGETS_PACKAGEMANAGER_H
#define WIDGETS_PACKAGEMANAGER_H

#include <QtCore/QObject>

#include "package.h"
#include "dockbaseproperties.h"

namespace Widgets
{

class PackageManagerPrivate;
class PackageManager : public QObject
{
    Q_OBJECT
public:
    explicit PackageManager(QObject *parent = 0);
    virtual ~PackageManager();
    Package * package(const QString &identifier);
    QStringList registeredPackages() const;
    Q_INVOKABLE QString dockFile(const QString &packageIdentifier, const QString &dockFilename);
    Q_INVOKABLE Widgets::DockBaseProperties * dock(const QString &packageIdentifier,
                                                   const QString &dockFilename);
    QStringList registeredDocks(const QString &packageIdentifier) const;
Q_SIGNALS:
//    void
public Q_SLOTS:
    void update();
protected:
    PackageManager(PackageManagerPrivate * dd, QObject *parent = 0);
    const QScopedPointer<PackageManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(PackageManager)
};

}

#endif // WIDGETS_PACKAGEMANAGER_H
