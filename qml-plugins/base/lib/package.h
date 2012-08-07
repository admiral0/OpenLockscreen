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

#ifndef WIDGETS_PACKAGE_H
#define WIDGETS_PACKAGE_H

/**
 * @file package.h
 * @short Definition of Widgets::Package
 */

#include "componentbase.h"

#include <QtCore/QPair>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "version.h"

namespace Widgets
{

class PackageManager;
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
 * he page about \ref packageCreationMetaSubsection "desktop file creation" provides more
 * information about how desktop files should be written.
 */
class Package: public ComponentBase
{
    Q_OBJECT
    /**
     * @short Package identifier
     */
    Q_PROPERTY(QString identifier READ identifier NOTIFY identifierChanged)
    /**
     * @short Package directory
     */
    Q_PROPERTY(QString directory READ directory NOTIFY directoryChanged)
    /**
     * @short Package plugin
     */
    Q_PROPERTY(QString plugin READ plugin NOTIFY pluginChanged)
    /**
     * @short Authors of the package
     */
    Q_PROPERTY(QString author READ author NOTIFY authorChanged)
    /**
     * @short Email of the authors of the package
     */
    Q_PROPERTY(QString email READ email NOTIFY emailChanged)
    /**
     * @short Website of the package
     */
    Q_PROPERTY(QString website READ website NOTIFY websiteChanged)
    /**
     * @short %Version of the package
     */
    Q_PROPERTY(Version version READ version NOTIFY versionChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit Package(QObject *parent = 0);
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
     * This method is used to create a Widgets::Package from desktop files.
     * If the desktop file could not be parsed, this method will return
     * a null pointer.
     *
     * @param desktopFile the desktop file to parse.
     * @param parent parent object for the created Widgets::Package.
     * @return a Widgets::Package.
     */
    static Package * fromDesktopFile(const QString &desktopFile, QObject *parent = 0);
Q_SIGNALS:
    /**
     * @brief Identifier changed
     */
    void identifierChanged();
    /**
     * @brief Directory changed
     */
    void directoryChanged();
    /**
     * @brief Plugin changed
     */
    void pluginChanged();
    /**
     * @brief Author changed
     */
    void authorChanged();
    /**
     * @brief Email changed
     */
    void emailChanged();
    /**
     * @brief Website changed
     */
    void websiteChanged();
    /**
     * @brief %Version changed
     */
    void versionChanged();
protected:
    /**
     * @brief Constructor for d-pointer
     * @param dd parent d-pointer.
     * @param parent parent object.
     */
    Package(PackagePrivate *dd, QObject *parent = 0);
private:
    /**
     * @brief Private constructor
     *
     * This private constructor is used to parse a desktop
     * file and extract the information.
     *
     * @param desktopFile desktop file.
     * @param parent parent object.
     */
    explicit Package(const QString &desktopFile, QObject *parent = 0);
    /**
     * @brief Set the package identifier
     * @param identifier package identifier.
     */
    void setIdentifier(const QString &identifier);
    /**
     * @brief Set the package directory
     * @param directory package directory.
     */
    void setDirectory(const QString &directory);
    /**
     * @brief Set the package plugin
     * @param plugin package plugin.
     */
    void setPlugin(const QString &plugin);
    /**
     * @brief Set the authors of the package
     * @param author authors of the package.
     */
    void setAuthor(const QString &author);
    /**
     * @brief Set the email of the authors of the package
     * @param email email of the authors of the package.
     */
    void setEmail(const QString &email);
    /**
     * @brief Set the website of the package
     * @param website website of the package.
     */
    void setWebsite(const QString &website);
    /**
     * @brief Set the version of the package
     * @param version version of the package.
     */
    void setVersion(const Version &version);
    /**
     * @brief Set if the package is visible
     * @param isVisible if the package is visible.
     */
    void setVisible(bool isVisible);
    /**
     * @brief Set the tags of this package
     * @param tags tags of this package.
     */
    void setTags(const QStringList tags);
    W_DECLARE_PRIVATE(Package)
    friend class PackageManager;
};

}

#endif // WIDGETS_PACKAGE_H
