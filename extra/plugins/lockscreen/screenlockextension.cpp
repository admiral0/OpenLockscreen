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

#include "screenlockextension.h"
#include "lockscreen.h"
#include <QtCore/QFile>
#include <QtGui/QGraphicsLinearLayout>
#include "notification/notificationmanager.h"
#include "notification/notificationparameter.h"
#include "notification/notificationparameters.h"
#include "notification/notificationwidgetparameterfactory.h"
#include "notificationsmodel.h"

Q_EXPORT_PLUGIN2(sysuid-screenlock, ScreenLockExtension)

ScreenLockExtension *ScreenLockExtension::instance_ = 0;

class ScreenLockExtension::ScreenLockExtensionPrivate
{
public:
    ScreenLockExtensionPrivate();
    virtual ~ScreenLockExtensionPrivate();
    void slotNotificationUpdated(const Notification &notification);
    void slotNotificationRemoved(uint notificationId);
    LockScreen *lockScreen;
    QGraphicsWidget *widget;
    NotificationManager *notificationManager;
    NotificationsModel *notificationsModel;
    ScreenLockExtensionInterface::ScreenLockMode mode;
};

ScreenLockExtension::ScreenLockExtensionPrivate::ScreenLockExtensionPrivate()
{
    lockScreen = 0;
    notificationManager = 0;
    notificationsModel = 0;
    widget = 0;
}

ScreenLockExtension::ScreenLockExtensionPrivate::~ScreenLockExtensionPrivate()
{
    if(lockScreen != 0) {
        lockScreen->deleteLater();
        widget->deleteLater();
    }
}

void ScreenLockExtension::ScreenLockExtensionPrivate::
                          slotNotificationUpdated(const Notification &notification)
{
    // Get notifications parameters
    NotificationParameters parameters = notification.parameters();
    QString body = parameters.value(NotificationWidgetParameterFactory::bodyKey()).toString();
    QString summary = parameters.value(NotificationWidgetParameterFactory::summaryKey()).toString();
    QString action = parameters.value(NotificationWidgetParameterFactory::actionKey()).toString();
    QString icon = parameters.value(NotificationWidgetParameterFactory::iconIdKey()).toString();

    notificationsModel->addNotification(body, summary, icon);
}

void ScreenLockExtension::ScreenLockExtensionPrivate::
                          slotNotificationRemoved(uint notificationId)
{

}

////// End of private class //////

ScreenLockExtension::ScreenLockExtension(QObject *parent) :
    QObject(parent), d(new ScreenLockExtensionPrivate())
{
    instance_ = this;
}

ScreenLockExtension::~ScreenLockExtension()
{
    delete d;
}

void ScreenLockExtension::reset()
{
}

void ScreenLockExtension::setNotificationManagerInterface(
                          NotificationManagerInterface &notificationManager) {

    d->notificationManager = static_cast<NotificationManager *>(&notificationManager);
    if(d->notificationManager != 0) {
        connect(d->notificationManager, SIGNAL(notificationUpdated(Notification)),
                this, SLOT(slotNotificationUpdated(Notification)));
    }

}

QObject * ScreenLockExtension::qObject()
{
    return this;
}

void ScreenLockExtension::setMode(ScreenLockMode mode)
{

}

bool ScreenLockExtension::initialize(const QString &interface)
{
    Q_UNUSED(interface)
    d->notificationsModel = new NotificationsModel(this);
    d->lockScreen = new LockScreen(d->notificationsModel);
    d->widget = new QGraphicsWidget();
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(d->widget);
    layout->setContentsMargins(0, 36, 0 , 0);
    layout->addItem(d->lockScreen);
    d->widget->setLayout(layout);

    connect(d->lockScreen, SIGNAL(unlocked()), this, SIGNAL(unlocked()));
    return true;
}

QGraphicsWidget *ScreenLockExtension::widget()
{
    return d->widget;
}

ScreenLockExtension * ScreenLockExtension::instance()
{
    return instance_;
}

NotificationManagerInterface *ScreenLockExtension::notificationManagerInterface()
{
    return d->notificationManager;
}

#include "moc_screenlockextension.cpp"
