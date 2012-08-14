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

#include "scrollingmanager.h"

namespace Widgets
{

namespace Background
{

class ScrollingManagerPrivate
{
public:
    ScrollingManagerPrivate(ScrollingManager *q);
    void computePosition();
    qreal position;
    qreal x;
    qreal initialX;
    qreal width;
    qreal pageWidth;
private:
    ScrollingManager * const q_ptr;
    Q_DECLARE_PUBLIC(ScrollingManager)
};

ScrollingManagerPrivate::ScrollingManagerPrivate(ScrollingManager *q):
    q_ptr(q)
{
    position = 0.;
    x = 0.;
    initialX = 0.;
    width = 0.;
    pageWidth = 0.;
}

void ScrollingManagerPrivate::computePosition()
{
    Q_Q(ScrollingManager);
    qreal effectiveWidth = width - pageWidth;
    qreal effectivePosition = x - initialX;
    qreal positionRatio = effectivePosition / effectiveWidth;

    if (position != positionRatio) {
        position = positionRatio;
        emit q->positionChanged();
    }
}

////// End of private class //////

ScrollingManager::ScrollingManager(QObject *parent) :
    QObject(parent), d_ptr(new ScrollingManagerPrivate(this))
{
}

ScrollingManager::~ScrollingManager()
{
}

qreal ScrollingManager::position() const
{
    Q_D(const ScrollingManager);
    return d->position;
}

qreal ScrollingManager::x() const
{
    Q_D(const ScrollingManager);
    return d->x;
}

qreal ScrollingManager::initialX() const
{
    Q_D(const ScrollingManager);
    return d->initialX;
}

qreal ScrollingManager::width() const
{
    Q_D(const ScrollingManager);
    return d->width;
}

qreal ScrollingManager::pageWidth() const
{
    Q_D(const ScrollingManager);
    return d->pageWidth;
}

void ScrollingManager::setX(qreal x)
{
    Q_D(ScrollingManager);
    if (d->x != x) {
        d->x = x;
        emit xChanged();
        d->computePosition();
    }
}

void ScrollingManager::setInitialX(qreal initialX)
{
    Q_D(ScrollingManager);
    if (d->initialX != initialX) {
        d->initialX = initialX;
        emit initialXChanged();
        d->computePosition();
    }
}

void ScrollingManager::setWidth(qreal width)
{
    Q_D(ScrollingManager);
    if (width < 0) {
        return;
    }

    if (d->width != width) {
        d->width = width;
        emit widthChanged();
        d->computePosition();
    }
}

void ScrollingManager::setPageWidth(qreal pageWidth)
{
    Q_D(ScrollingManager);
    if (pageWidth < 0) {
        return;
    }

    if (d->pageWidth != pageWidth) {
        d->pageWidth = pageWidth;
        emit pageWidthChanged();
        d->computePosition();
    }
}

}

}
