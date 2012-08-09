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

#ifndef WIDGETS_CONFIGURATIONMANAGER_H
#define WIDGETS_CONFIGURATIONMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include "widgetproperties.h"
#include "dockproperties.h"

namespace Widgets
{

class ConfigurationManagerPrivate;
class ConfigurationManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Widgets::DockProperties * currentDock READ currentDock WRITE setCurrentDock
               NOTIFY currentDockChanged)
    Q_PROPERTY(Widgets::WidgetProperties * currentWidget READ currentWidget WRITE setCurrentWidget
               NOTIFY currentWidgetChanged)
public:
    explicit ConfigurationManager(QObject *parent = 0);
    virtual ~ConfigurationManager();
    DockProperties *currentDock() const;
    WidgetProperties *currentWidget() const;
Q_SIGNALS:
    void currentDockChanged();
    void currentWidgetChanged();
    void saveDockSettingsRequested();
    void saveWidgetSettingsRequested();
public Q_SLOTS:
    void setCurrentDock(Widgets::DockProperties *currentDock);
    void setCurrentWidget(Widgets::WidgetProperties *currentWidget);
    void requestSaveDockSettings();
    void requestSaveWidgetSettings();
    void saveDockSettings(const QVariantMap &settings);
    void saveWidgetSettings(const QVariantMap &settings);
protected:
    QScopedPointer <ConfigurationManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(ConfigurationManager)
};

}

#endif // WIDGETS_CONFIGURATIONMANAGER_H
