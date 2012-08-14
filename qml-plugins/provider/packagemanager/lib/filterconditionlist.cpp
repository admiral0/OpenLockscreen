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

/**
 * @file filterconditionlist.cpp
 * @short Implementation of Widgets::Provider::PackageManager::FilterConditionList
 */

#include "filterconditionlist.h"

#include <QtCore/QStringList>
#include <QtCore/QDebug>

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

/**
 * @internal
 * @brief Private class for Widgets::Provider::PackageManager::FilterConditionList
 */
class FilterConditionListPrivate
{
public:
    /**
     * @internal
     * @brief Filter condition
     *
     * This method is here for interfacing with QML.
     *
     * @param list declarative list property.
     * @param entry filter condition.
     */
    static void appendCondition(QDeclarativeListProperty<FilterCondition> *list,
                                FilterCondition *entry);
    /**
     * @internal
     * @brief Filters
     */
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

FilterConditionList::~FilterConditionList()
{
}

QDeclarativeListProperty<FilterCondition> FilterConditionList::filter()
{
    return QDeclarativeListProperty<FilterCondition>(this, 0,
                                                     FilterConditionListPrivate::appendCondition);
}


QStringList FilterConditionList::tags() const
{
    Q_D(const FilterConditionList);
    QStringList values;

    foreach (FilterCondition *condition, d->conditions) {
        if (!condition->tag().isEmpty()) {
            values.append(condition->tag());
        }
    }
    return values;
}

}

}

}
