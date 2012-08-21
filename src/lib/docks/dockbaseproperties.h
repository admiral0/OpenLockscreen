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

#ifndef WIDGETS_DOCKS_DOCKBASEPROPERTIES_H
#define WIDGETS_DOCKS_DOCKBASEPROPERTIES_H

/**
 * @file dockbaseproperties.h
 * @short Definition of Widgets::Docks::DockBaseProperties
 */

#include "graphicalcomponentbase.h"

#include <QtCore/QMetaType>

namespace Widgets
{

namespace Docks
{

class DockBasePropertiesPrivate;
/**
 * @brief Base properties for docks
 *
 * This class is used to represent all the
 * base properties that a dock have. Base
 * properties includes their inherent
 * properties that should be constant.
 *
 * These properties are all related to position and
 * size of the dock:
 * - width()
 * - height()
 * - anchorsTop()
 * - anchorsBottom()
 * - anchorsLeft()
 * - anchorsRight()
 */
class DockBaseProperties: public GraphicalComponentBase
{
    Q_OBJECT
    /**
     * @short Width
     */
    Q_PROPERTY(int width READ width CONSTANT)
    /**
     * @short Height
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
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit DockBaseProperties(QObject *parent = 0);
    /**
     * @brief Default constructor
     *
     * @param fileName filename of the dock.
     * @param disambiguation disambiguation parameter of the dock.
     * @param settingsFileName filename of the settings dock.
     * @param width width.
     * @param height height.
     * @param anchorsTop if the dock is anchored using top anchor.
     * @param anchorsBottom if the dock is anchored using bottom anchor.
     * @param anchorsLeft if the dock is anchored using left anchor.
     * @param anchorsRight if the dock is anchored using right anchor.
     * @param parent
     */
    explicit DockBaseProperties(const QString &fileName, const QVariantMap &disambiguation,
                                const QString &settingsFileName,
                                int width, int height,
                                bool anchorsTop, bool anchorsBottom,
                                bool anchorsLeft, bool anchorsRight,
                                QObject *parent = 0);
    /**
     * @brief Width
     * @return width.
     */
    int width() const;
    /**
     * @brief Height
     * @return height.
     */
    int height() const;
    /**
     * @brief If the dock is anchored using top anchor
     * @return if the dock is anchored using top anchor
     */
    bool anchorsTop() const;
    /**
     * @brief If the dock is anchored using top anchor
     * @return if the dock is anchored using top anchor.
     */
    bool anchorsBottom() const;
    /**
     * @brief If the dock is anchored using top anchor
     * @return if the dock is anchored using top anchor.
     */
    bool anchorsLeft() const;
    /**
     * @brief If the dock is anchored using top anchor
     * @return if the dock is anchored using top anchor.
     */
    bool anchorsRight() const;
    /**
     * @brief Get information from QML file
     *
     * This methiod is a conveinent method that
     * extracts informations about the dock and
     * creates a dock base properties from a QML file.
     *
     * @param qmlFile path to the QML file.
     * @param disambiguation disambituation parameter.
     * @param settingsFileName settings component file name.
     * @param parent parent object.
     * @return the widget base properties.
     */
    static DockBaseProperties * fromQmlFile(const QString &qmlFile,
                                            const QVariantMap &disambiguation,
                                            const QString &settingsFileName,
                                            QObject *parent = 0);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    explicit DockBaseProperties(DockBasePropertiesPrivate *dd, QObject *parent);
private:
    W_DECLARE_PRIVATE(DockBaseProperties)
};

}

}

Q_DECLARE_METATYPE(Widgets::Docks::DockBaseProperties *)

#endif // WIDGETS_DOCKS_DOCKBASEPROPERTIES_H
