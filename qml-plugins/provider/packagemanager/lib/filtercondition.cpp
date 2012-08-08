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

#include "filtercondition.h"

namespace Widgets
{

class FilterConditionPrivate
{
public:
    QString tag;
};

////// End of private class //////

FilterCondition::FilterCondition(QObject *parent) :
    QObject(parent), d_ptr(new FilterConditionPrivate())
{
}

FilterCondition::FilterCondition(FilterConditionPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

FilterCondition::~FilterCondition()
{
}

QString FilterCondition::tag() const
{
    Q_D(const FilterCondition);
    return d->tag;
}

void FilterCondition::setTag(const QString &tag)
{
    Q_D(FilterCondition);
    if (d->tag != tag) {
        d->tag = tag;
        emit tagChanged(tag);
    }
}

}
