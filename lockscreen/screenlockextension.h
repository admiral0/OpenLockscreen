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

#ifndef SCREENLOCKEXTENSION_H
#define SCREENLOCKEXTENSION_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include "screenlockextensioninterface.h"
#include "notification/notification.h"

class ScreenLockExtension : public QObject, public ScreenLockExtensionInterface
{
    Q_OBJECT
    Q_INTERFACES(ScreenLockExtensionInterface MApplicationExtensionInterface)
public:
    explicit ScreenLockExtension(QObject *parent = 0);
    virtual ~ScreenLockExtension();

    virtual void reset();
    virtual void setNotificationManagerInterface(NotificationManagerInterface &notificationManager);
    virtual QObject *qObject();
    virtual void setMode(ScreenLockExtensionInterface::ScreenLockMode mode);
    virtual bool initialize(const QString &interface);
    virtual QGraphicsWidget *widget();

    static ScreenLockExtension *instance();
    NotificationManagerInterface *notificationManagerInterface();
Q_SIGNALS:
    void notifierSinkActive(bool active);
    void unlocked();
private:
    class ScreenLockExtensionPrivate;
    ScreenLockExtensionPrivate * const d;

    Q_PRIVATE_SLOT(d, void slotNotificationUpdated(const Notification &notification))
    Q_PRIVATE_SLOT(d, void slotNotificationRemoved(uint notificationId))

    static ScreenLockExtension *instance_;
};

#endif // SCREENLOCKEXTENSION_H
