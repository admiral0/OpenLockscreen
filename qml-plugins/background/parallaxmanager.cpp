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

/**
 * @file parallaxmanager.cpp
 * @short Implementation of Widgets::Background::ParallaxManager
 */

#include "parallaxmanager.h"

namespace Widgets
{

namespace Background
{

/**
 * @internal
 * @short Private class for Widgets::Background::ParallaxManager
 */
class ParallaxManagerPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    ParallaxManagerPrivate(ParallaxManager *q);
    /**
     * @internal
     * @brief Compute position
     */
    void computePosition();
    /**
     * @internal
     * @brief Position
     */
    qreal position;
    /**
     * @internal
     * @brief Content x
     */
    qreal contentX;
    /**
     * @internal
     * @brief Initial content x
     */
    qreal initialContentX;
    /**
     * @internal
     * @brief Content width
     */
    qreal contentWidth;
    /**
     * @internal
     * @brief View width
     */
    qreal viewWidth;
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    ParallaxManager * const q_ptr;
    Q_DECLARE_PUBLIC(ParallaxManager)
};

ParallaxManagerPrivate::ParallaxManagerPrivate(ParallaxManager *q):
    q_ptr(q)
{
    position = 0.;
    contentX = 0.;
    initialContentX = 0.;
    contentWidth = 0.;
    viewWidth = 0.;
}

void ParallaxManagerPrivate::computePosition()
{
    Q_Q(ParallaxManager);
    qreal effectiveWidth = contentWidth - viewWidth;
    qreal effectivePosition = contentX - initialContentX;
    qreal positionRatio = effectivePosition / effectiveWidth;

    if (position != positionRatio) {
        position = positionRatio;
        emit q->positionChanged();
    }
}

////// End of private class //////

ParallaxManager::ParallaxManager(QObject *parent) :
    QObject(parent), d_ptr(new ParallaxManagerPrivate(this))
{
}

ParallaxManager::~ParallaxManager()
{
}

qreal ParallaxManager::position() const
{
    Q_D(const ParallaxManager);
    return d->position;
}

qreal ParallaxManager::contentX() const
{
    Q_D(const ParallaxManager);
    return d->contentX;
}

qreal ParallaxManager::initialContentX() const
{
    Q_D(const ParallaxManager);
    return d->initialContentX;
}

qreal ParallaxManager::contentWidth() const
{
    Q_D(const ParallaxManager);
    return d->contentWidth;
}

qreal ParallaxManager::viewWidth() const
{
    Q_D(const ParallaxManager);
    return d->viewWidth;
}

void ParallaxManager::setContentX(qreal contentX)
{
    Q_D(ParallaxManager);
    if (d->contentX != contentX) {
        d->contentX = contentX;
        emit contentXChanged();
        d->computePosition();
    }
}

void ParallaxManager::setInitialContentX(qreal initialContentX)
{
    Q_D(ParallaxManager);
    if (d->initialContentX != initialContentX) {
        d->initialContentX = initialContentX;
        emit initialContentXChanged();
        d->computePosition();
    }
}

void ParallaxManager::setContentWidth(qreal contentWidth)
{
    Q_D(ParallaxManager);
    if (contentWidth < 0) {
        return;
    }

    if (d->contentWidth != contentWidth) {
        d->contentWidth = contentWidth;
        emit contentWidthChanged();
        d->computePosition();
    }
}

void ParallaxManager::setViewWidth(qreal viewWidth)
{
    Q_D(ParallaxManager);
    if (viewWidth < 0) {
        return;
    }

    if (d->viewWidth != viewWidth) {
        d->viewWidth = viewWidth;
        emit viewWidthChanged();
        d->computePosition();
    }
}

}

}
