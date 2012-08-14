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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_FILTERCONDITIONLIST_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_FILTERCONDITIONLIST_H

/**
 * @file filterconditionlist.h
 * @short Definition of Widgets::Provider::PackageManager::FilterConditionList
 */


#include <QtCore/QObject>
#include <QtDeclarative/QDeclarativeListProperty>

#include "filtercondition.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class FilterConditionListPrivate;

/**
 * @brief Filters for the packagemanager
 *
 * This class is used to provides some filters
 * for the package manager. It is used to group
 * a set of Widgets::Provider::PackageManager::FilterConditionList
 * in order to create a list.
 */
class FilterConditionList: public QObject
{
    Q_OBJECT
    /**
     * @short Filter
     */
    Q_PROPERTY(QDeclarativeListProperty<Widgets::Provider::PackageManager::FilterCondition>
               filter READ filter)
    Q_CLASSINFO("DefaultProperty", "filter")
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit FilterConditionList(QObject *parent = 0);
    /**
     * @brief Destructors
     */
    virtual ~FilterConditionList();
    /**
     * @brief Filter
     * @return A declarative list property that is used to manage the filter.
     */
    QDeclarativeListProperty<FilterCondition> filter();
    /**
     * @brief Tags
     *
     * This method is used to convert the filter list to
     * a list of tags, that are used in the package manager
     * to filter the entries.
     *
     * @return tags.
     */
    QStringList tags() const;
Q_SIGNALS:
    void conditionListChanged();
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<FilterConditionListPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FilterConditionList)
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_FILTERCONDITIONLIST_H
