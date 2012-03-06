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
#include <QtGui/QGraphicsLinearLayout>
#include <QFile>

Q_EXPORT_PLUGIN2(sysuid-screenlock, ScreenLockExtension)

ScreenLockExtension *ScreenLockExtension::instance_ = 0;

class ScreenLockExtension::ScreenLockExtensionPrivate
{
public:
    ScreenLockExtensionPrivate();
    virtual ~ScreenLockExtensionPrivate();
    Widgets::LockScreen *lockScreen;
    QGraphicsWidget *widget;
    NotificationManagerInterface *notificationManager;
};

ScreenLockExtension::ScreenLockExtensionPrivate::ScreenLockExtensionPrivate()
{
    lockScreen = 0;
    notificationManager = 0;
}

ScreenLockExtension::ScreenLockExtensionPrivate::~ScreenLockExtensionPrivate()
{
    if(lockScreen != 0) {
        lockScreen->deleteLater();
    }
    if(widget != 0) {
        widget->deleteLater();
    }
}

////// End of private class //////

ScreenLockExtension::ScreenLockExtension(QObject *parent) :
    QObject(parent), d(new ScreenLockExtensionPrivate())
{
    instance_ = this;
    connect(this, SIGNAL(unlocked()), this, SLOT(slotUnlocked()));
}

ScreenLockExtension::~ScreenLockExtension()
{
    delete d;
}

void ScreenLockExtension::reset()
{
//    d->lockScreen->reset();
}

void ScreenLockExtension::setNotificationManagerInterface(
                          NotificationManagerInterface &notificationManager) {
    d->notificationManager = &notificationManager;
}

QObject * ScreenLockExtension::qObject()
{
    return this;
}

void ScreenLockExtension::setMode(ScreenLockMode mode)
{
//    d->lockScreen->setMode(mode);
}

bool ScreenLockExtension::initialize(const QString &interface)
{
    Q_UNUSED(interface)

    d->lockScreen = new Widgets::LockScreen();
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
//    return d->lockScreen;
}

ScreenLockExtension * ScreenLockExtension::instance()
{
    return instance_;
}

NotificationManagerInterface *ScreenLockExtension::notificationManagerInterface()
{
    return d->notificationManager;
}
