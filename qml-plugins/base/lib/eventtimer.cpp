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
 * @file eventtimer.cpp
 * @short Implementation of Widgets::EventTimer
 */

#include "eventtimer.h"

#include <QtCore/QCoreApplication>

namespace Widgets
{

static const int DEFAULT_INTERVAL = 15;

/**
 * @internal
 * @brief Private class for Widgets::EventTimer
 */
class EventTimerPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    EventTimerPrivate(EventTimer *q);
    /**
     * @internal
     * @brief Post an event
     *
     * This method is used to post an event,
     * that will be processed by the event timer.
     *
     * It is also responsible of incrementing the
     * timer and emitting the EventTimer::triggered()
     * signal, as well as stopping the timer.
     *
     * The timer stops when the timer attribute is
     * >= interval.
     */
    void postEvent();
    /**
     * @internal
     * @brief Timer
     */
    int timer;
    /**
     * @internal
     * @brief Interval
     */
    int interval;
private:
    /**
     * @brief Q-pointer
     */
    EventTimer * const q_ptr;
    Q_DECLARE_PUBLIC(EventTimer)
};

EventTimerPrivate::EventTimerPrivate(EventTimer *q):
    q_ptr(q)
{
    timer = -1;
    interval = DEFAULT_INTERVAL;
}

void EventTimerPrivate::postEvent()
{
    Q_Q(EventTimer);
    timer ++;

    if (timer < interval) {
        QEvent *event = new QEvent(QEvent::Timer);
        QCoreApplication::postEvent(q, event);
    } else {
        timer = -1;
        emit q->runningChanged();
        emit q->triggered();
    }

}

////// End of private class //////

EventTimer::EventTimer(QObject *parent) :
    QObject(parent), d_ptr(new EventTimerPrivate(this))
{
}

EventTimer::~EventTimer()
{
}

bool EventTimer::isRunning() const
{
    Q_D(const EventTimer);
    return (d->timer > -1);
}

int EventTimer::interval() const
{
    Q_D(const EventTimer);
    return d->interval;
}

void EventTimer::setInterval(int interval)
{
    Q_D(EventTimer);
    if (interval < 0) {
        return;
    }

    if (d->interval != interval) {
        d->interval = interval;
        emit intervalChanged();
    }
}

void EventTimer::start()
{
    Q_D(EventTimer);
    d->postEvent();
    emit runningChanged();
}

bool EventTimer::event(QEvent *e)
{
    Q_D(EventTimer);
    if (e->type() == QEvent::Timer) {
        d->postEvent();
    }
    return QObject::event(e);
}

}
