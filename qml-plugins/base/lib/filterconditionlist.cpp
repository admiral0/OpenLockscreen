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

#include "filterconditionlist.h"

#include <QtCore/QStringList>
#include <QtCore/QDebug>

namespace Widgets
{

class FilterConditionListPrivate
{
public:
    static void appendCondition(QDeclarativeListProperty<FilterCondition> *list,
                                FilterCondition *entry);
    QList<FilterCondition *> conditions;
};

void FilterConditionListPrivate::appendCondition(QDeclarativeListProperty<FilterCondition> *list,
                                                 FilterCondition *entry)
{
    FilterConditionList *conditionList = qobject_cast<FilterConditionList *>(list->object);
    if(conditionList) {
        conditionList->d_func()->conditions.append(entry);
        emit conditionList->conditionListChanged();
    }
}

////// End of private class //////

FilterConditionList::FilterConditionList(QObject *parent):
    QObject(parent), d_ptr(new FilterConditionListPrivate())
{
}

FilterConditionList::FilterConditionList(FilterConditionListPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

FilterConditionList::~FilterConditionList()
{
}

QDeclarativeListProperty<FilterCondition> FilterConditionList::conditions()
{
    return QDeclarativeListProperty<FilterCondition>(
                this, 0, Widgets::FilterConditionListPrivate::appendCondition);
}


QStringList FilterConditionList::tags() const
{
    Q_D(const FilterConditionList);
    QStringList subrequests;

    foreach (FilterCondition *condition, d->conditions) {
        if (!condition->tag().isEmpty()) {
            subrequests.append(condition->tag());
        }
    }
    return subrequests;
}

}
