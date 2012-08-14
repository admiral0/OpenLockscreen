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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_DESKTOPCOMPONENT_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_DESKTOPCOMPONENT_H

/**
 * @file desktopcomponent.h
 * @short Definition of Widgets::Provider::PackageManager::DesktopComponent
 */

#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "widgets_global.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class DesktopComponentPrivate;
/**
 * @brief A desktop component
 *
 * This class is used to represent all the informations that
 * are shared between all desktop components.
 *
 * Those informations are
 * - icon(), that is an icon for the component.
 * - defaultName(), that is the name that of the component without any translation
 *   (usually in english).
 * - name(), that is the translated name, if available.
 * - defaultDescription(), that is the description, or comment of the component without any
 *   translation (usually in english).
 * - description(), that is the translated description, if available.
 *
 * The page about \ref packageCreationMetaSubsection "desktop file creation" provides more
 * information about how desktop files should be written.
 */
class DesktopComponent: public QObject
{
    Q_OBJECT
    /**
     * @short Icon of the component
     */
    Q_PROPERTY(QString icon READ icon CONSTANT)
    /**
     * @short Default name of the component
     */
    Q_PROPERTY(QString defaultName READ defaultName CONSTANT)
    /**
     * @short Name of the component
     *
     * This property hold the translated name of this component, using
     * the system locales. If a translation cannot be found, the default
     * name is used instead.
     */
    Q_PROPERTY(QString name READ name CONSTANT)
    /**
     * @short Default description of the component
     */
    Q_PROPERTY(QString defaultDescription READ defaultDescription CONSTANT)
    /**
     * @short Description of the component
     *
     * This property hold the translated description of this component, using
     * the system locales. If a translation cannot be found, the default
     * description is used instead.
     */
    Q_PROPERTY(QString description READ description CONSTANT)
public:
    /**
     * @brief Default constructor
     * @param icon icon of the component.
     * @param defaultName default name of the component.
     * @param defaultDescription default description of the component.
     * @param names a list of names associated to the language.
     * @param descriptions a list of descriptions associated to the language.
     * @param parent parent object.
     */
    explicit DesktopComponent(const QString &icon,
                              const QString &defaultName, const QString &defaultDescription,
                              const QHash<QString, QString> &names,
                              const QHash<QString, QString> &descriptions,
                              QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DesktopComponent();
    /**
     * @short Icon of the component
     * @return icon of the component.
     */
    QString icon() const;
    /**
     * @brief Languages
     *
     * This method is used to get a list of
     * languages that are available, either
     * for the name or for the description.
     *
     * @return languages.
     */
    QStringList languages() const;
    /**
     * @brief Default name of the component
     * @return default name of the component.
     */
    QString defaultName() const;
    /**
     * @short Name of the component
     * @return name of the component.
     */
    QString name() const;
    /**
     * @short Name of the component
     *
     * @param language language of the name.
     * @return name of the component in the given language.
     */
    QString name(const QString &language) const;
    /**
     * @short Default description of the component
     * @return default description of the component.
     */
    QString defaultDescription() const;
    /**
     * @short Description of the component
     * @return description of the component.
     */
    QString description() const;
    /**
     * @short Description of the component
     *
     * @param language language of the description.
     * @return description of the component in the given language.
     */
    QString description(const QString &language) const;
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    DesktopComponent(DesktopComponentPrivate *dd, QObject *parent = 0);
    /**
     * @brief D-pointer
     */
    const QScopedPointer<DesktopComponentPrivate> d_pointer;
private:
    W_DECLARE_PRIVATE(DesktopComponent)

};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_DESKTOPCOMPONENT_H
