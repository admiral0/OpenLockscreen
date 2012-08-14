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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_FILTERCONDITION_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_FILTERCONDITION_H

/**
 * @file filtercondition.h
 * @short Definition of Widgets::Provider::PackageManager::FilterCondition
 */

#include <QtCore/QObject>

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class FilterConditionPrivate;

/**
 * @brief An entry in the package manager filter
 *
 * This container class is used to provide filter entries in
 * the package manager. It is available in QML, and should be
 * provided as lists, inside a FilterConditionList.
 */
class FilterCondition : public QObject
{
    Q_OBJECT
    /**
     * @short Tag
     */
    Q_PROPERTY(QString tag READ tag WRITE setTag NOTIFY tagChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit FilterCondition(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~FilterCondition();
    /**
     * @brief Tag
     * @return tag.
     */
    QString tag() const;
signals:
    /**
     * @brief Tag changed
     */
    void tagChanged();
public slots:
    /**
     * @brief Set tag
     * @param tag tag.
     */
    void setTag(const QString &tag);
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<FilterConditionPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FilterCondition)
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_FILTERCONDITION_H
