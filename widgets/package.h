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
 * @file package.h
 * @short Definition of Widgets::Package
 *
 * This file contains the definition of the
 * Widgets::Package class.
 */

#ifndef WIDGETS_PACKAGE_H
#define WIDGETS_PACKAGE_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include "widgetbaseproperties.h"
#include "dockbaseproperties.h"

namespace Widgets
{

/**
 * @short Information about a widget package
 *
 * This class is used to parse an information file
 * that should be included in all widgets package in
 * order to provide informations about the widgets
 * contained in the package.
 *
 * A package object can be created from a package
 * information file using fromInformationFile().
 *
 * @section infoFile Information file format
 *
 * The information file must have this layout :
 *
 * @code
 <package id="packageIdentifier"
          name="Package name" description="Set of basic widgets.">
     <widget name="Widget 1 name"
             qmlfile="Widget1.qml"
             hassettings="false">
         <size width="200" height="200" />
     </widget>
     <widget name="Widget 2 name"
             qmlfile="Widget2.qml"
             hassettings="true">
         <size width="200" height="200" />
     </widget>
     <dock name="Dock name"
           qmlfile="Dock.qml"
           hassettings="false">
         <size width="100" heigh="100" />
         <anchors top="false" bottom="false" left="false" right="false" />
     </dock>
 </package>
 @endcode
 *
 * @section visibility Visibility
 *
 * Some packages may be hidden from the widget / dock
 * selectors. It can be the case if the package contains
 * widgets that are use internally. In this case, in the
 * package section, a visible="false" attribute should
 * be added.
 *
 * @see packaging
 */
class Package
{
public:
    /**
     * @short Default constructor
     *
     * This constructor is used to create a package
     * containing all the needed informations.
     *
     * Most of the time, it is less costly to parse
     * an information file using fromInformationFile().
     *
     * @param name name of the package.
     * @param identifier identifier of the package.
     * @param description description of the package.
     * @param isVisible if the package is visible.
     * @param widgets widgets that this package provides.
     * @param docks docks that this package provides.
     */
    explicit Package(const QString &name, const QString &identifier, const QString &description,
                     bool isVisible,
                     const QList<WidgetBaseProperties *> widgets,
                     const QList<DockBaseProperties *> docks);
    /**
     * @short Copy constructor
     *
     * @param other the package to copy.
     */
    Package(const Package &other);
    /**
     * @short Implementation of =
     *
     * @param other the package to be assigned.
     * @return A reference to this object.
     */
    Package & operator=(const Package &other);
    /**
     * @short Destructor
     */
    virtual ~Package();
    /**
     * @short Package identifier
     *
     * This method is used to retrieve the
     * package identifier.
     *
     * @return the package identifier.
     */
    QString identifier() const;
    /**
     * @short Package name
     *
     * This method is used to retrieve the
     * package name.
     *
     * @return the package name.
     */
    QString name() const;
    /**
     * @short Package description
     *
     * This method is used to retrieve the
     * description of a package.
     *
     * @return description of the package.
     */
    QString description() const;
    /**
     * @short If the package is visible
     * 
     * This method is used to retrive
     * if the package is visible.
     * 
     * @return if the package is visible.
     */
    bool isVisible() const;
    /**
     * @short Widgets
     *
     * This method is used to retrieve the
     * widgets that this package provides.
     *
     * @return widgets that this package provides.
     */
    QList<WidgetBaseProperties *> widgets() const;
    /**
     * @short Docks
     *
     * This method is used to retrieve the
     * docks that this package provides.
     *
     * @return docks that this package provides.
     */
    QList<DockBaseProperties *> docks() const;
    /**
     * @short Create a package object from an information file
     *
     * This method creates a package object
     * based on an information file.
     *
     * @param filePath path to the information file.
     * @param parent parent object for WidgetBaseProperties that are created.
     * @return a Package created from the information file.
     */
    static Package fromInformationFile(const QString &filePath, QObject *parent = 0);
private:
    class PackagePrivate;
    /**
     * @short D-pointer
     */
    PackagePrivate * const d;
};

}

#endif // PACKAGE_H
