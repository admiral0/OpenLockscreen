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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_DESKTOPCOMPONENT_P_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_DESKTOPCOMPONENT_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file desktopcomponent_p.h
 * @short Definition of Widgets::Provider::PackageManager::DesktopComponentPrivate
 */

#include "desktopcomponent.h"
#include "builderpatterninterfaces_p.h"

#include <QtCore/QHash>
#include <QtCore/QStringList>


namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class DesktopFileParser;
/**
 * @internal
 * @brief Private class for Widgets::Provider::PackageManager::DesktopComponent
 */
class DesktopComponentPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    DesktopComponentPrivate(DesktopComponent *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DesktopComponentPrivate();
    /**
     * @internal
     * @brief Default name
     */
    QString defaultName;
    /**
     * @internal
     * @brief Default description
     */
    QString defaultDescription;
    /**
     * @internal
     * @brief Translated names
     */
    QHash<QString, QString> names;
    /**
     * @internal
     * @brief Translated descriptions
     */
    QHash<QString, QString> descriptions;
    /**
     * @internal
     * @brief Icon
     */
    QString icon;
    /**
     * @internal
     * @brief Q-pointer
     */
    DesktopComponent *const q_ptr;
private:
    Q_DECLARE_PUBLIC(DesktopComponent)
};

/**
 * @internal
 * @brief Helper class for component builder for
 *        Widgets::Provider::PackageManager::DesktopComponentComponentBuilderHelper
 *
 * This helper class provides all the information for the
 * builder class to create the component. It take cares of the
 * desktop file, and parse it, and store the parent of the new
 * component as well.
 *
 * These parameters are set using setProperties().
 *
 * It also provides an information about the validity of the desktop file
 * element, that can be retrieved using isValid().
 */
class DesktopComponentBuilderHelper
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit DesktopComponentBuilderHelper();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DesktopComponentBuilderHelper();
    /**
     * @internal
     * @brief Set properties
     *
     * @param desktopFile Desktop file to parse.
     * @param parent parent object.
     */
    virtual void setProperties(const QString &desktopFile, QObject *parent = 0);
    /**
     * @internal
     * @brief parent
     * @return parent object.
     */
    QObject *parent() const;
    /**
     * @internal
     * @brief If the desktop file is valid
     *
     * This method is used in AbstractBuilder::buildElement() in
     * order to check if the XML element contains
     * valid information.
     *
     * @return if the XML element is valid.
     */
    virtual bool isValid() const;
    /**
     * @internal
     * @brief Default name
     * @return default name.
     */
    QString defaultName() const;
    /**
     * @internal
     * @brief Default description
     * @return default description.
     */
    QString defaultDescription() const;
    /**
     * @internal
     * @brief Names
     * @return names.
     */
    QHash<QString, QString> names() const;
    /**
     * @internal
     * @brief Descriptions
     * @return descriptions.
     */
    QHash<QString, QString> descriptions() const;
    /**
     * @internal
     * @brief Icon
     * @return icon.
     */
    QString icon() const;
protected:
    /**
     * @internal
     * @brief Desktop file parser
     */
    DesktopFileParser *desktopFileParser;
private:
    /**
     * @internal
     * @brief Parent object
     */
    QObject *m_parent;
};

/**
 * @internal
 * @brief Component builder for
 *        Widgets::Provider::PackageManager::DesktopComponentComponentBuilderHelper
 *
 * This class is used to get a
 * Widgets::Provider::PackageManager::DesktopComponentComponentBuilderHelper
 * from a desktop file.
 *
 * This class build the component in 2 steps.
 * - call to setProperties() to get the desktop file path and parent object.
 * - call to buildElement() to build the component.
 */
class DesktopComponentBuilder: public AbstractBuilder<DesktopComponent *>
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit DesktopComponentBuilder();
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DesktopComponentBuilder();
    /**
     * @internal
     * @brief Set properties
     *
     * @param desktopFile Desktop file to parse.
     * @param parent parent object.
     */
    virtual void setProperties(const QString &desktopFile, QObject *parent = 0);
    /**
     * @internal
     * @brief Built the component
     */
    virtual void buildElement();
private:
    /**
     * @internal
     * @brief Helper class
     */
    DesktopComponentBuilderHelper *m_helper;
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_DESKTOPCOMPONENT_P_H
