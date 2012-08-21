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

#ifndef WIDGETS_PROVIDER_PACKAGEMANAGER_PACKAGE_H
#define WIDGETS_PROVIDER_PACKAGEMANAGER_PACKAGE_H

/**
 * @file package.h
 * @short Definition of Widgets::Provider::PackageManager::Package
 */

#include "desktopcomponent.h"

#include <QtCore/QPair>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "version.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

class PackagePrivate;
/**
 * @brief A package
 *
 * This class is used to represent a package. It handles
 * a lot of information that are provided through the desktop files,
 * and can be accessed through QML.
 *
 * Those informations are
 * - identifier(), that is the unique identifier of the package.
 * - directory(), that is the directory where the package is.
 * - plugin(), that is the name of the plugin for libwidgets.
 * @todo this plugin is not loaded, or not even taken in account.
 *
 * - author(), that is the name of the authors of the package.
 * - email(), that is the email of the authors of the package.
 * - website(), that is the website the package.
 * - version(), that is the version of the package.
 * - isVisible(), that is used to check if the package is visible and should be displayed
 * while requested from the package manager.
 * - tags(), that are the list of tags that this package have.
 *
 * These informations are extended with those that are shared
 * with the other components, and that are provided through
 * Widgets::ComponentBase.
 *
 * The page about \ref packageCreationMetaSubsection "desktop file creation" provides more
 * information about how desktop files should be written.
 */
class Package: public DesktopComponent
{
    Q_OBJECT
    /**
     * @short Package identifier
     */
    Q_PROPERTY(QString identifier READ identifier CONSTANT)
    /**
     * @short Package directory
     */
    Q_PROPERTY(QString directory READ directory CONSTANT)
    /**
     * @short Package plugin
     */
    Q_PROPERTY(QString plugin READ plugin CONSTANT)
    /**
     * @short Authors of the package
     */
    Q_PROPERTY(QString author READ author CONSTANT)
    /**
     * @short Email of the authors of the package
     */
    Q_PROPERTY(QString email READ email CONSTANT)
    /**
     * @short Website of the package
     */
    Q_PROPERTY(QString website READ website CONSTANT)
    /**
     * @short %Version of the package
     */
    Q_PROPERTY(Version version READ version CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Package(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param icon icon of the component.
     * @param defaultName default name of the component.
     * @param defaultDescription default description of the component.
     * @param names a list of names associated to the language.
     * @param descriptions a list of descriptions associated to the language.
     * @param identifier package identifier.
     * @param directory package directory.
     * @param plugin package plugin.
     * @param author author of the package.
     * @param email email of the package.
     * @param website website of the package.
     * @param version version of the package.
     * @param visible if the package is visible.
     * @param tags tags of the package.
     * @param parent parent object.
     */
    explicit Package(const QString &icon,
                     const QString &defaultName, const QString &defaultDescription,
                     const QMap<QString, QString> &names,
                     const QMap<QString, QString> &descriptions,
                     const QString &identifier,
                     const QString &directory,
                     const QString &plugin,
                     const QString &author,
                     const QString &email,
                     const QString &website,
                     const Version &version,
                     bool visible = true,
                     const QStringList &tags = QStringList(),
                     QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~Package();
    /**
     * @brief Package identifier
     * @return package identifier.
     */
    QString identifier() const;
    /**
     * @brief Package directory
     * @return package directory.
     */
    QString directory() const;
    /**
     * @brief Package plugin
     * @return package plugin.
     */
    QString plugin() const;
    /**
     * @brief Authors of the package
     * @return authors of the package.
     */
    QString author() const;
    /**
     * @brief Email of the authors of the package
     * @return email of the authors of the package.
     */
    QString email() const;
    /**
     * @brief Website of the package
     * @return website of the package.
     */
    QString website() const;
    /**
     * @brief %Version of the package
     * @return version of the package.
     */
    Version version() const;
    /**
     * @brief If the package is visible
     * @return if the package is visible.
     */
    bool isVisible() const;
    /**
     * @brief Tags of this package
     * @return tags of this package.
     */
    QStringList tags() const;
    /**
     * @brief Create a package from a desktop file
     *
     * @param desktopFile path to the desktop file to parse.
     * @param parent parent object for the created package.
     * @return a package.
     */
    static Package * fromDesktopFile(const QString &desktopFile, QObject *parent = 0);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    Package(PackagePrivate *dd, QObject *parent = 0);
private:
    W_DECLARE_PRIVATE(Package)
};

}

}

}

#endif // WIDGETS_PROVIDER_PACKAGEMANAGER_PACKAGE_H
