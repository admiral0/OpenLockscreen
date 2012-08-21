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
 * @file dockbaseproperties.h
 * @short Definition of Widgets::DockBaseProperties
 *
 * This file contains the definition of the
 * Widgets::DockBaseProperties class.
 */

#ifndef WIDGETS_DOCKBASEPROPERTIES_H
#define WIDGETS_DOCKBASEPROPERTIES_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include "mappableelementinterface.h"

namespace Widgets
{

/**
 * @short Base properties for a dock
 *
 * This class is used to store properties
 * for a dock that is not created yet.
 *
 * This class stores these properties
 * - name of the dock
 * - dock's width and height
 * - where the docks anchors
 * - package where the dock is from and file to create it
 * - if the dock has settings
 * 
 * Remark : the QML file used to create the
 * dock is provided as an absolute path.
 *
 * Each of these properties can be access
 * either using getter methods or using
 * properties, in a QML context.
 *
 * Please note that all the properties
 * are constant and they should be passed
 * through the constructor.
 */
class DockBaseProperties : public QObject, public MappableElementInterface
{
    Q_OBJECT
    /**
     * @short Name of the dock
     */
    Q_PROPERTY(QString name READ name CONSTANT)
    /**
     * @short Width of the dock
     */
    Q_PROPERTY(int width READ width CONSTANT)
    /**
     * @short Height of the dock
     */
    Q_PROPERTY(int height READ height CONSTANT)
    /**
     * @short If the dock is anchored using top anchor
     */
    Q_PROPERTY(bool anchorsTop READ anchorsTop CONSTANT)
    /**
     * @short If the dock is anchored using bottom anchor
     */
    Q_PROPERTY(bool anchorsBottom READ anchorsBottom CONSTANT)
    /**
     * @short If the dock is anchored using left anchor
     */
    Q_PROPERTY(bool anchorsLeft READ anchorsLeft CONSTANT)
    /**
     * @short If the dock is anchored using right anchor
     */
    Q_PROPERTY(bool anchorsRight READ anchorsRight CONSTANT)
    /**
     * @short QML file used to create the dock
     */
    Q_PROPERTY(QString qmlFile READ qmlFile CONSTANT)
    /**
     * @short Package which the dock belongs to
     */
    Q_PROPERTY(QString package READ package CONSTANT)
    /**
     * @short If the dock has settings
     */
    Q_PROPERTY(bool hasSettings READ hasSettings CONSTANT)
public:
    /**
     * @short Invalid constructor
     *
     * This constructor is not used and creates an empty
     * dock base properties with no property. It is used for QML type
     * implementation.
     *
     * @param parent parent object.
     */
    explicit DockBaseProperties(QObject *parent = 0);
    /**
     * @short Default constructor
     *
     * This constructor is used to create a dock base
     * properties containing all the needed properties.
     *
     * @param name name of the dock.
     * @param width width of the dock.
     * @param height height of the dock.
     * @param anchorsTop if the dock is anchors using top anchor.
     * @param anchorsBottom if the dock is anchors using bottom anchor.
     * @param anchorsLeft if the dock is anchors using left anchor.
     * @param anchorsRight if the dock is anchors using right anchor.
     * @param qmlFile QML file used to create the dock.
     * @param package package which the dock belongs to.
     * @param hasSettings if the dock has settings.
     * @param parent parent object.
     */
    explicit DockBaseProperties(const QString &name, int width, int height,
                                bool anchorsTop, bool anchorsBottom,
                                bool anchorsLeft, bool anchorsRight,
                                const QString &qmlFile, const QString &package = QString(),
                                bool hasSettings = false,
                                QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~DockBaseProperties();
    /**
     * @short Name of the dock
     *
     * This method is used to retrieve the name of
     * the dock.
     *
     * @return name of the dock.
     */
    QString name() const;
    /**
     * @short Width of the dock
     *
     * This method is used to retrieve the width of
     * the dock.
     *
     * @return width of the dock.
     */
    int width() const;
    /**
     * @short Height of the dock
     *
     * This method is used to retrieve the height of
     * the dock.
     *
     * @return height of the dock.
     */
    int height() const;
    /**
     * @short If the dock is anchors using top anchor
     *
     * This method is used to retrieve if the dock
     * is anchored using top anchor.
     *
     * @return if the dock is anchored using top anchor.
     */
    bool anchorsTop() const;
    /**
     * @short If the dock is anchors using bottom anchor
     *
     * This method is used to retrieve if the dock
     * is anchored using bottom anchor.
     *
     * @return if the dock is anchored using bottom anchor.
     */
    bool anchorsBottom() const;
    /**
     * @short If the dock is anchors using left anchor
     *
     * This method is used to retrieve if the dock
     * is anchored using left anchor.
     *
     * @return if the dock is anchored using left anchor.
     */
    bool anchorsLeft() const;
    /**
     * @short If the dock is anchors using right anchor
     *
     * This method is used to retrieve if the dock
     * is anchored using right anchor.
     *
     * @return if the dock is anchored using right anchor.
     */
    bool anchorsRight() const;
    /**
     * @short QML file used to create the dock
     *
     * This method is used to retrieve the QML file
     * used to create the dock.
     *
     * @return QML file used to create the dock.
     */
    QString qmlFile() const;
    /**
     * @short Package which the dock belongs to
     *
     * This method is used to retrieve the package
     * which the dock belongs to.
     *
     * @return package which the dock belongs to.
     */
    QString package() const;
    /**
     * @short If the widget has settings
     *
     * This method is used to check if the widget
     * has settings.
     *
     * @return if the widget has settings.
     */
    bool hasSettings() const;
    /**
     * @short To map
     *
     * This method copies the content
     * of this class into a map. This
     * makes saving easier.
     *
     * @return the content of this class as a map.
     */
    virtual QVariantMap toMap() const;
private:
    class DockBasePropertiesPrivate;
    /**
     * @short D-pointer
     */
    DockBasePropertiesPrivate * const d;

};

}

Q_DECLARE_METATYPE(Widgets::DockBaseProperties*)

#endif // WIDGETS_DOCKBASEPROPERTIES_H
