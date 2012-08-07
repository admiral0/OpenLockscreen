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

#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H

#include <QtGui/QGraphicsProxyWidget>
#include <QtDeclarative/QDeclarativeView>

class NotificationsModel;
class LockScreen : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    LockScreen(NotificationsModel *notificationsModel, QGraphicsWidget *parent = 0);
signals:
    void unlocked();
private:
    QDeclarativeView *view;
};

#endif // LOCKSCREEN_H
