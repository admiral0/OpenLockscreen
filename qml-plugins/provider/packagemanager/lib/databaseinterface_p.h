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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.


#include <QtCore/QObject>
#include <QtCore/QVariantHash>

namespace Widgets
{

class WidgetBaseProperties;
namespace Docks {
class DockBaseProperties;
}

namespace Provider
{

namespace PackageManager
{

class FilterConditionList;
class DatabaseInterfacePrivate;
class DatabaseInterface: public QObject
{
    Q_OBJECT
public:
    explicit DatabaseInterface(QObject *parent = 0);
    virtual ~DatabaseInterface();
    QVariantHash disambiguation(const QString &value);
    static QString packageIdentifier(const QVariantHash &disambiguation);
    void prepareDatabase();
    void clean();
    void scan();
    QStringList registeredPackages(FilterConditionList *filter) const;
    QStringList registeredWidgets(const QString &packageIdentifier) const;
    QStringList registeredDocks(const QString &packageIdentifier) const;
    QString widgetFile(const QString &packageIdentifier, const QString &fileName);
    QString widgetSettingsFile(const QString &packageIdentifier, const QString &fileName);
    WidgetBaseProperties * widget(const QString &packageIdentifier, const QString &fileName,
                                  QObject *parent = 0);
    QString dockFile(const QString &packageIdentifier, const QString &fileName);
    QString dockSettingsFile(const QString &packageIdentifier, const QString &fileName);
    Docks::DockBaseProperties * dock(const QString &packageIdentifier, const QString &fileName,
                                     QObject *parent = 0);
protected:
    QScopedPointer <DatabaseInterfacePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DatabaseInterface)
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_DATABASEINTERFACE_P_H
