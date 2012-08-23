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

#include "lockscreenmanager.h"
#include <QtCore/QFile>

LockScreenManager::LockScreenManager(QObject *parent) :
    QObject(parent)
{
    m_visible = true;
    m_unlocked = false;
    m_state = new MeeGo::QmDisplayState(this);

    connect(m_state, SIGNAL(displayStateChanged(MeeGo::QmDisplayState::DisplayState)),
            this, SLOT(slotDisplayStateChanged(MeeGo::QmDisplayState::DisplayState)));
}

bool LockScreenManager::isVisible() const
{
    return m_visible;
}

void LockScreenManager::unlock()
{
    setVisible(false);
    m_unlocked = true;
    emit unlocked();
}

void LockScreenManager::setVisible(bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        emit visibleChanged();
    }
}


void LockScreenManager::slotDisplayStateChanged(MeeGo::QmDisplayState::DisplayState state)
{
    switch(state) {
    case MeeGo::QmDisplayState::On:
        if (!m_unlocked) {
            setVisible(true);
        }
        break;
    case MeeGo::QmDisplayState::Off:
        m_unlocked = false;
        setVisible(false);
        break;
    default:
        break;

    }
}
