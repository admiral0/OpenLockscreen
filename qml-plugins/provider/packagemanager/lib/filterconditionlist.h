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

#ifndef WIDGETS_FILTERCONDITIONLIST_H
#define WIDGETS_FILTERCONDITIONLIST_H

#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeListProperty>

#include "filtercondition.h"

namespace Widgets
{

class FilterConditionListPrivate;
class FilterConditionList: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<Widgets::FilterCondition> conditions
               READ conditions)
    Q_CLASSINFO("DefaultProperty", "conditions")
public:
    explicit FilterConditionList(QObject *parent = 0);
    virtual ~FilterConditionList();
    QDeclarativeListProperty<FilterCondition> conditions();
    QStringList tags() const;
Q_SIGNALS:
    void conditionListChanged();
protected:
    explicit FilterConditionList(FilterConditionListPrivate *dd, QObject *parent = 0);
    const QScopedPointer<FilterConditionListPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FilterConditionList)
};

}

#endif // WIDGETS_FILTERCONDITIONLIST_H
