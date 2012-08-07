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

#ifndef WIDGETS_COMPONENTBASE_P_H
#define WIDGETS_COMPONENTBASE_P_H

/**
 * @file componentbase_p.h
 * @short Definition of Widgets::ComponentBasePrivate
 */

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include <QtCore/QHash>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "componentbase.h"

namespace Widgets
{

class DesktopParser;
/**
 * @internal
 * @brief Private class for Widgets::ComponentBase
 */
class ComponentBasePrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    ComponentBasePrivate(ComponentBase *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~ComponentBasePrivate();
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
     * @brief Translated names and descriptions
     *
     * This hash stores the translated names and
     * descriptions, associating the country and
     * language code to a pair that contains
     * the name and the description.
     */
    QHash<QString, QPair<QString, QString> > nameAndDescription;
    /**
     * @internal
     * @brief Icon
     */
    QString icon;
    /**
     * @internal
     * @brief If the file is valid
     */
    bool valid;
    /**
     * @internal
     * @brief Parse from desktop file
     *
     * This method parse the desktop file and store
     * the loaded content. It uses parseDesktopFile()
     * and checkValid().
     *
     * @param file path to the desktop file to parse.
     */
    void fromDesktopFile(const QString &file);
protected:
    /**
     * @internal
     * @brief Parse the desktop file
     *
     * This method is used to get the informations from
     * the desktop file and store it.
     *
     * You should reimplement this method in subclasses
     * to parse more specialized desktop files.
     *
     * @param parser parser used to parse the desktop file.
     */
    virtual void parseDesktopFile(const DesktopParser &parser);
    /**
     * @internal
     * @brief Check if the desktop file is valid
     *
     * This method is used to check if the parsed data
     * are valid before storing them.
     *
     * You should reimplement this method in subclasses
     * to parse more specialized desktop files.
     *
     * @param parser parser used to parse the desktop file.
     * @return if the parsed data are valid.
     */
    virtual bool checkValid(const DesktopParser &parser);
    /**
     * @internal
     * @brief Q-pointer
     */
    ComponentBase *const q_ptr;
private:
    Q_DECLARE_PUBLIC(ComponentBase)
};

}

#endif // WIDGETS_COMPONENTBASE_P_H
