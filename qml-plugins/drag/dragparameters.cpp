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

#include "dragparameters.h"

namespace Widgets
{

namespace Drag
{

class DragParametersPrivate
{
public:
    QString removeButtonSource;
    QString editButtonSource;
};

////// End of private class //////

DragParameters::DragParameters(QObject *parent) :
    QObject(parent), d_ptr(new DragParametersPrivate())
{
}

DragParameters::~DragParameters()
{
}

QString DragParameters::removeButtonSource() const
{
    Q_D(const DragParameters);
    return d->removeButtonSource;
}

QString DragParameters::editButtonSource() const
{
    Q_D(const DragParameters);
    return d->editButtonSource;
}

void DragParameters::setRemoveButtonSource(const QString &removeButtonSource)
{
    Q_D(DragParameters);
    if (d->removeButtonSource != removeButtonSource) {
        d->removeButtonSource = removeButtonSource;
        emit removeButtonSourceChanged();
    }
}

void DragParameters::setEditButtonSource(const QString &editButtonSource)
{
    Q_D(DragParameters);
    if (d->editButtonSource != editButtonSource) {
        d->editButtonSource = editButtonSource;
        emit editButtonSourceChanged();
    }
}

}

}
