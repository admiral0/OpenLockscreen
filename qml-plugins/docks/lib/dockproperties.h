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

#ifndef WIDGETS_DOCKS_DOCKPROPERTIES_H
#define WIDGETS_DOCKS_DOCKPROPERTIES_H

/**
 * @file dockproperties.h
 * @short Definition of Widgets::Docks::DockProperties
 */

#include "dockbaseproperties.h"

#include <QtCore/QMetaType>
#include <QtCore/QVariantMap>

#include "identifiedelementinterface.h"

namespace Widgets
{

namespace Docks
{

class DockPropertiesPrivate;

/**
 * @brief Dock properties
 *
 * This class is used to represent a dock,
 * with all the dynamical properties.
 *
 * These properties are
 * - identifier()
 * - settings()
 *
 * The identifier is an unique identifier, using an UUID, that
 * is used to uniquely identify a widget. Settings is a parameter
 * that docks can use to store and retrieve some settings.
 */
class DockProperties: public DockBaseProperties, private IdentifiedElementInterface
{
    Q_OBJECT
    /**
     * @short Identifier
     */
    Q_PROPERTY(QString identifier READ identifier CONSTANT)
    /**
     * @short Settings
     */
    Q_PROPERTY(QVariantHash settings READ settings NOTIFY settingsChanged)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit DockProperties(QObject *parent = 0);
    /**
     * @brief Constructor
     *
     * This constructor is used to create a dock properties
     * based on the properties stored in the dock base
     * properties plus additional parameters.
     *
     * The identifier is not passed, and is automatically
     * generated.
     *
     * @param base dock base properties.
     * @param settings settings.
     * @param parent parent object.
     */
    explicit DockProperties(DockBaseProperties *base,
                            const QVariantHash &settings = QVariantHash(),
                            QObject *parent = 0);
    /**
     * @brief Constructor
     *
     * This constructor is used to create a dock properties
     * based on the properties stored in the dock base
     * properties plus additional parameters.
     *
     * @param base dock base properties.
     * @param identifier identifier.
     * @param settings settings.
     * @param parent parent object.
     */
    explicit DockProperties(DockBaseProperties *base,
                            const QString &identifier,
                            const QVariantHash &settings = QVariantHash(),
                            QObject *parent = 0);
    /**
     * @brief Identifier
     * @return identifier.
     */
    QString identifier() const;
    /**
     * @short Settings
     * @return settings.
     */
    QVariantHash settings() const;
public Q_SLOTS:
    /**
     * @short Set the settings
     * @param settings settings.
     */
    void setSettings(const QVariantHash &settings);
Q_SIGNALS:
    /**
     * @short Settings changed changed
     */
    void settingsChanged();
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    DockProperties(DockPropertiesPrivate *dd, QObject *parent);
private:
    W_DECLARE_PRIVATE(DockProperties)
};

}

}

Q_DECLARE_METATYPE(Widgets::Docks::DockProperties *)

#endif // WIDGETS_DOCKS_DOCKPROPERTIES_H
