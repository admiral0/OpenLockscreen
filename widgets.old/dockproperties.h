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
 * @file dockproperties.h
 * @short Definition of Widgets::DockProperties
 *
 * This file contains the definition of the
 * Widgets::DockProperties class.
 */

#ifndef WIDGETS_DOCKPROPERTIES_H
#define WIDGETS_DOCKPROPERTIES_H

#include "dockbaseproperties.h"
#include "identifiedelementinterface.h"
#include "elementsettings.h"

namespace Widgets
{
/**
 * @short Properties for a displayed dock
 *
 * This class is used to store properties
 * for a dock that is displayed.
 *
 * This class stores these properties
 * - identifier of the dock
 * - settings specific to this dock
 *
 * Each of these properties can be access
 * either using getter methods or using
 * properties, in a QML context.
 */
class DockProperties : public DockBaseProperties, private IdentifiedElementInterface
{
    Q_OBJECT
    /**
     * @short Identifier
     */
    Q_PROPERTY(QString identifier READ identifier CONSTANT)
    /**
     * @short Settings that belongs to this widget
     */
    Q_PROPERTY(Widgets::ElementSettings * settings READ settings NOTIFY settingsChanged)
public:
    /**
     * @short Invalid constructor
     *
     * This constructor is not used and creates an empty
     * dock properties with no property. It is used for QML type
     * implementation.
     *
     * @param parent parent object.
     */
    explicit DockProperties(QObject *parent = 0);
    /**
     * @short Default constructor
     *
     * This constructor is used to create a dock
     * properties containing all the needed properties
     * and an auto-generated identifier.
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
     * @param settings settings that belongs to the dock.
     * @param parent parent object.
     */
    explicit DockProperties(const QString &name, int width, int height,
                            bool anchorsTop, bool anchorsBottom,
                            bool anchorsLeft, bool anchorsRight,
                            const QString &qmlFile, const QString &package,
                            bool hasSettings,
                            const QVariantMap &settings = QVariantMap(),
                            QObject *parent = 0);
    /**
     * @short Overloaded constructor
     *
     * This constructor is used to create a dock
     * properties containing all the needed properties
     * while setting the identifier.
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
     * @param identifier identifier of the dock.
     * @param settings settings that belongs to the dock.
     * @param parent parent object.
     */
    explicit DockProperties(const QString &name, int width, int height,
                            bool anchorsTop, bool anchorsBottom,
                            bool anchorsLeft, bool anchorsRight,
                            const QString &qmlFile, const QString &package,
                            bool hasSettings,
                            const QString &identifier,
                            const QVariantMap &settings = QVariantMap(),
                            QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~DockProperties();
    /**
     * @short Identifier
     *
     * This method is used to retrieve the identifier
     * that is used to uniquely identify this dock.
     *
     * @return this dock's identifier.
     */
    QString identifier() const;
    /**
     * @short Settings that belongs to this dock
     *
     * This method is used to retrieve the settings
     * that belongs to this dock.
     *
     * @return settings that belongs to this dock.
     */
    Widgets::ElementSettings * settings() const;
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
Q_SIGNALS:
    /**
     * @short Settings changed
     *
     * Notify that the settings has
     * changed.
     *
     * @param settings value of the new settings.
     */
    void settingsChanged(Widgets::ElementSettings *settings);
public Q_SLOTS:
    /**
     * @short Set the settings that belongs to this dock
     *
     * This method is used to set the
     * settings that belongs to this dock.
     *
     * @param settings settings to set.
     */
    void setSettings(const QVariantMap &settings);
private:
    class DockPropertiesPrivate;
    /**
     * @short D-pointer
     */
    DockPropertiesPrivate * const d;
};

}

Q_DECLARE_METATYPE(Widgets::DockProperties *)

#endif // WIDGETS_DOCKPROPERTIES_H
