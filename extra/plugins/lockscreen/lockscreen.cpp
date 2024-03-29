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

#include "lockscreen.h"


#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeError>
#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>

#include "lockscreenmanager.h"
#include "notificationsmodel.h"
#include "settingsmanager.h"

LockScreen::LockScreen(NotificationsModel *notificationsModel, QGraphicsWidget *parent):
    QGraphicsProxyWidget(parent)
{
    LockScreenManager *manager = new LockScreenManager(this);

    QCoreApplication::instance()->setOrganizationName("SfietKonstantin");
    QCoreApplication::instance()->setApplicationName("Widgets");

    SettingsManager *settingsManager = new SettingsManager(this);

    QDBusConnection::sessionBus().registerService("org.SfietKonstantin.widgets");
    QDBusConnection::sessionBus().registerObject("/org/SfietKonstantin/widgets", settingsManager,
                                                 QDBusConnection::ExportAllSlots);

    view = new QDeclarativeView();
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view->rootContext()->setContextProperty("LockScreenManager", manager);
    view->rootContext()->setContextProperty("NotificationsModel", notificationsModel);
    view->rootContext()->setContextProperty("SettingsManagerInstance", settingsManager);
    view->setSource(QUrl("/opt/widgets/lockscreen/qml/main.qml"));

    setWidget(view);

    connect(manager, SIGNAL(unlocked()), this , SIGNAL(unlocked()));
}
