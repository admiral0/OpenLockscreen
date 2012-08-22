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

#ifndef LOCKSCEENMANAGER_H
#define LOCKSCEENMANAGER_H

#include <QtCore/QObject>
#include <qmsystem2/qmdisplaystate.h>

class LockScreenManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible NOTIFY visibleChanged)
public:
    explicit LockScreenManager(QObject *parent = 0);
    bool isVisible() const;
Q_SIGNALS:
    void unlocked();
    void visibleChanged();
public Q_SLOTS:
    void unlock();
private:
    void setVisible(bool visible);
    MeeGo::QmDisplayState *m_state;
    bool m_visible;
    bool m_unlocked;
private slots:
    void slotDisplayStateChanged(MeeGo::QmDisplayState::DisplayState state);

};

#endif // LOCKSCEENMANAGER_H
