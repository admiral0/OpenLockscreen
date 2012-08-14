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

#ifndef WIDGETS_BACKGROUND_SCROLLINGMANAGER_H
#define WIDGETS_BACKGROUND_SCROLLINGMANAGER_H

#include <QtCore/QObject>

namespace Widgets
{

namespace Background
{

class ScrollingManagerPrivate;
class ScrollingManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal position READ position NOTIFY positionChanged)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal initialX READ initialX WRITE setInitialX NOTIFY initialXChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal pageWidth READ pageWidth WRITE setPageWidth NOTIFY pageWidthChanged)
public:
    explicit ScrollingManager(QObject *parent = 0);
    virtual ~ScrollingManager();
    qreal position() const;
    qreal x() const;
    qreal initialX() const;
    qreal width() const;
    qreal pageWidth() const;
Q_SIGNALS:
    void positionChanged();
    void xChanged();
    void initialXChanged();
    void widthChanged();
    void pageWidthChanged();
public Q_SLOTS:
    void setX(qreal x);
    void setInitialX(qreal initialX);
    void setWidth(qreal width);
    void setPageWidth(qreal pageWidth);
protected:
    QScopedPointer<ScrollingManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(ScrollingManager)
};

}

}

#endif // WIDGETS_BACKGROUND_SCROLLINGMANAGER_H
