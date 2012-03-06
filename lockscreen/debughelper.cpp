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

#include "debughelper.h"
#include <QtCore/QFile>


namespace Widgets
{

class DebugHelper::DebugHelperPrivate
{
public:
    DebugHelperPrivate(DebugHelper *parent);
    ~DebugHelperPrivate();
    QFile * file;
    bool ok;
};

DebugHelper::DebugHelperPrivate::DebugHelperPrivate(DebugHelper *parent)
{
    file = new QFile("/home/developer/log", parent);
    ok = file->open(QIODevice::WriteOnly | QIODevice::Append);
}

DebugHelper::DebugHelperPrivate::~DebugHelperPrivate()
{
    if(ok) {
        file->close();
    }
}

////// End of private class //////

DebugHelper::DebugHelper(QObject *parent) :
    QObject(parent), d(new DebugHelperPrivate(this))
{
}

DebugHelper::~DebugHelper()
{
    delete d;
}

void DebugHelper::debug(const QString &data)
{
    if(d->ok) {
        d->file->write(data.toUtf8());
        d->file->write("\n");
    }
}

}
