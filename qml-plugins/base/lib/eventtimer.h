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

#ifndef WIDGETS_EVENTTIMER_H
#define WIDGETS_EVENTTIMER_H

/**
 * @file eventtimer.h
 * @short Definition of Widgets::EventTimer
 */

#include <QtCore/QObject>

namespace Widgets
{

class EventTimerPrivate;

/**
 * @brief Helper class for a timer based on events
 *
 * This timer is an event based timer. Unlike other timers,
 * it do not measure time, but is used to be triggered when
 * a certain number of loops in the event loop passed.
 *
 * The number of loops can be set using the interval()
 * property. The timer is started using start() and
 * use triggered() to notify the end.
 *
 * This counter is useful in some cases, for example
 * while a QML component is resizing, or to deal with
 * the very buggy ListView.
 */
class EventTimer : public QObject
{
    Q_OBJECT
    /**
     * @short If the timer is running
     */
    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)
    /**
     * @short Timer interval
     */
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit EventTimer(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~EventTimer();
    /**
     * @brief If the timer is running
     * @return if the timer is running.
     */
    bool isRunning() const;
    /**
     * @brief Timer interval
     * @return timer interval.
     */
    int interval() const;
Q_SIGNALS:
    /**
     * @brief Running changed
     */
    void runningChanged();
    /**
     * @brief Interval changed
     */
    void intervalChanged();
    /**
     * @brief Triggered
     *
     * This signal is emitted when the timer
     * is triggered.
     */
    void triggered();
public Q_SLOTS:
    /**
     * @brief Set interval
     * @param interval interval.
     */
    void setInterval(int interval);
    /**
     * @brief Start the timer
     */
    void start();
protected:
    /**
     * @brief Reimplementation of event
     *
     * This reimplementation is done to enable the
     * event timer.
     *
     * @param e event to react to.
     * @return if the event succeeded.
     */
    bool event(QEvent *e);
    /**
     * @brief D-pointer
     */
    QScopedPointer<EventTimerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(EventTimer)

};

}

#endif // WIDGETS_EVENTTIMER_H
