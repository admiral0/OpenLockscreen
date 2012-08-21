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

#ifndef WIDGETS_VERSION_H
#define WIDGETS_VERSION_H

/**
 * @file version.h
 * @short Definition of Widgets::Version
 */

#include <QtCore/QMetaType>
#include <QtCore/QScopedPointer>

namespace Widgets
{

class VersionPrivate;
/**
 * @brief %Version
 *
 * This class is used to contain a version. It provides
 * comparisons between versions and can be used to detect
 * beta versions.
 *
 * Versions are in the form X.Y.Z, where X, Y and Z should
 * be positive integers.
 *
 * Comparison between versions is a bit tricky. Since software
 * with the same major and minor version, but a different patch
 * version are not very different, comparison do not take patch
 * in account, except for ==
 *
 * For example, we have
 * - 1.1.0 > 1.0.0
 * - 1.1.1 >= 1.1.0 and 1.1.1 <= 1.1.0, but 1.1.1 != 1.1.0
 * - 1.1.1 is not > 1.1.0, but 1.2.0 > 1.1.0
 *
 * Remark: if you try to compare a version with an invalid one, all
 * comparison operators will return false, except !=, that will be true.
 *
 * A beta version is such as the minor version >= Widgets::BETA_LIMIT.
 */
class Version
{
public:
    /**
     * @brief Invalid constructor
     *
     * This constructor creates an invalid version.
     */
    explicit Version();
    /**
     * @brief Default constructor
     *
     * @param major major version.
     * @param minor minor version.
     * @param patch patch version.
     */
    explicit Version(int major, int minor = 0, int patch = 0);
    /**
     * @brief Copy constructor
     * @param other other version.
     */
    Version(const Version &other);
    /**
     * @brief Assignment operator
     * @param other the other version to assign.
     * @return a reference to this object.
     */
    Version &operator=(const Version &other);
    /**
     * @short Destructor
     */
    ~Version();
    /**
     * @brief Operator ==
     * @param other the other version to compare with.
     * @return if the two versions are equal.
     */
    bool operator==(const Version &other);
    /**
     * @brief Operator !=
     * @param other the other version to compare with.
     * @return if the two versions are different.
     */
    bool operator!=(const Version &other);
    /**
     * @brief Operator >
     * @param other the other version to compare with.
     * @return if this version is strictly greater than the other.
     */
    bool operator>(const Version &other);
    /**
     * @brief Operator >=
     * @param other the other version to compare with.
     * @return if this version is greater or equal to the other.
     */
    bool operator>=(const Version &other);
    /**
     * @brief Operator <
     * @param other the other version to compare with.
     * @return if this version is strictly lesser than the other.
     */
    bool operator<(const Version &other);
    /**
     * @brief Operator <=
     * @param other the other version to compare with.
     * @return if this version is lesser or equal to the other.
     */
    bool operator<=(const Version &other);
    /**
     * @brief Major version.
     * @return major version.
     */
    int major() const;
    /**
     * @brief Minor version.
     * @return minor version.
     */
    int minor() const;
    /**
     * @brief Patch version.
     * @return patch version.
     */
    int patch() const;
    /**
     * @brief If the version is valid.
     * @return if the version is valid.
     */
    bool isValid() const;
    /**
     * @brief isBeta
     * @return
     */
    bool isBeta() const;
    /**
     * @brief Current version of libwidgets
     *
     * This method is used to get the current version of
     * libwidgets.
     *
     * @return the current version of libwidgets.
     */
    static Version currentVersion();
    /**
     * @brief %Version from a string
     *
     * This method is used to parse a version, in X.Y.Z
     * format from a string to a version.
     *
     * @param version the string to parse.
     * @return the version corresponding to the string.
     */
    static Version fromString(const QString &version);
    /**
     * @brief %Version as a string
     *
     * This method is used to represent this version as
     * a string, in X.Y.Z format.
     *
     * @return this version as a string.
     */
    QString toString() const;
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     */
    Version(VersionPrivate * dd);
    /**
     * @brief D-pointer
     */
    const QScopedPointer<VersionPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(Version)
};

}

Q_DECLARE_METATYPE(Widgets::Version)

#endif // WIDGETS_VERSION_H
