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

#include <QTextStream>
#include <QFile>

LockScreenManager::LockScreenManager(QObject *parent) :
    QObject(parent)
{
}

void LockScreenManager::unlock()
{
    debug("Unlocked");
    emit unlocked();
}

void LockScreenManager::debug(const QString &value)
{
    QFile * outFile = new QFile("/home/developer/lockscreenlog", this);
    if (!outFile->open(QIODevice::WriteOnly | QIODevice::Append)) {
        return;
    }
    outFile->write(value.toAscii());
    outFile->write("\n");
    outFile->close();
}
