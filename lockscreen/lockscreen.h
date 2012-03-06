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

#ifndef WIDGETS_LOCKSCREEN_H
#define WIDGETS_LOCKSCREEN_H

#include <QtGui/QGraphicsProxyWidget>
//#include <QtGui/QGraphicsWidget>
#include "screenlockextensioninterface.h"

namespace Widgets
{

//class LockScreen : public QGraphicsObject, public QGraphicsLayoutItem
class LockScreen : public QGraphicsProxyWidget
//class LockScreen : public QGraphicsWidget
{
    Q_OBJECT
public:
    LockScreen(QGraphicsWidget *parent = 0);
//    virtual QRectF boundingRect() const;
//    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
Q_SIGNALS:
    void unlocked();
public Q_SLOTS:
    void reset();
    void setMode(ScreenLockExtensionInterface::ScreenLockMode mode);
//private Q_SLOTS:
//    void slotSetGeometry();
private:
    class LockScreenPrivate;
    LockScreenPrivate * const d;
};

}

#endif // WIDGETS_LOCKSCREEN_H
