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

#ifndef WIDGETS_WIDGETPROPERTIES_H
#define WIDGETS_WIDGETPROPERTIES_H

/**
 * @file widgetproperties.h
 * @short Definition of Widgets::WidgetProperties
 */

#include "widgetbaseproperties.h"

#include <QtCore/QMetaType>
#include <QtCore/QVariantMap>

#include "identifiedelementinterface.h"

namespace Widgets
{

class WidgetPropertiesPrivate;
/**
 * @brief Widget properties
 *
 * This class is used to represent a widget,
 * with all position properties, and other
 * dynamical properties.
 *
 * These properties are
 * - identifier()
 * - x()
 * - y()
 * - z()
 * - width()
 * - height()
 * - settings()
 * - visible()
 *
 * The identifier is an unique identifier, using an UUID, that
 * is used to uniquely identify a widget. x, y, z, width and height
 * are related the the geometry of the widget. Settings is a parameter
 * that widgets can use to store and retrieve some settings. Finally,
 * visible stores the visibility of the widget.
 */
class WidgetProperties: public WidgetBaseProperties, private IdentifiedElementInterface
{
    Q_OBJECT
    /**
     * @short Identifier
     */
    Q_PROPERTY(QString identifier READ identifier CONSTANT)
    /**
     * @short X coordinate
     */
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    /**
     * @short Y coordinate
     */
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    /**
     * @short Z coordinate
     */
    Q_PROPERTY(int z READ z WRITE setZ NOTIFY zChanged)
    /**
     * @short Width
     */
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    /**
     * @short Height
     */
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    /**
     * @short Visibility
     */
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    /**
     * @short Settings
     */
    Q_PROPERTY(QVariantMap settings READ settings WRITE setSettings NOTIFY settingsChanged)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit WidgetProperties(QObject *parent = 0);
    /**
     * @brief Constructor
     *
     * This constructor is used to create a widget properties
     * based on the properties stored in the widget base
     * properties plus additional parameters.
     *
     * The identifier is not passed, and is automatically
     * generated.
     *
     * @param base widget base properties.
     * @param x x coordinate.
     * @param y y coordinate.
     * @param z z coordinate.
     * @param width width.
     * @param height height.
     * @param settings settings.
     * @param parent parent object.
     */
    explicit WidgetProperties(WidgetBaseProperties *base,
                              int x, int y, int z, int width, int height,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    /**
     * @brief Constructor
     *
     * This constructor is used to create a widget properties
     * based on the properties stored in the widget base
     * properties plus additional parameters.
     *
     * @param base widget base properties.
     * @param identifier identifier.
     * @param x x coordinate.
     * @param y y coordinate.
     * @param z z coordinate.
     * @param width width.
     * @param height height.
     * @param settings settings.
     * @param parent parent object.
     */
    explicit WidgetProperties(WidgetBaseProperties *base,
                              const QString &identifier,
                              int x, int y, int z, int width, int height,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    /**
     * @brief Identifier
     * @return identifier.
     */
    QString identifier() const;
    /**
     * @short X coordinate
     * @return x coordinate.
     */
    int x() const;
    /**
     * @short Y coordinate
     * @return y coordinate.
     */
    int y() const;
    /**
     * @short Z coordinate
     * @return z coordinate.
     */
    int z() const;
    /**
     * @short Width
     * @return width.
     */
    int width() const;
    /**
     * @short Height
     * @return height.
     */
    int height() const;
    /**
     * @short Visibility
     * @return visibility.
     */
    bool isVisible() const;
    /**
     * @short Settings
     * @return settings.
     */
    QVariantMap settings() const;
public Q_SLOTS:
    /**
     * @short Set the x coordinate
     * @param x x coordinate.
     */
    void setX(int x);
    /**
     * @short Set the y coordinate
     * @param y y coordinate.
     */
    void setY(int y);
    /**
     * @short Set the z coordinate
     * @param z z coordinate.
     */
    void setZ(int z);
    /**
     * @short Set the width
     * @param width width.
     */
    void setWidth(int width);
    /**
     * @short Set the height
     * @param height height.
     */
    void setHeight(int height);
    /**
     * @short Set the visibility
     * @param visible if the widget is visible.
     */
    void setVisible(bool visible);
    /**
     * @short Set the settings
     * @param settings settings.
     */
    void setSettings(const QVariantMap &settings);
Q_SIGNALS:
    /**
     * @short X coordinate changed
     */
    void xChanged();
    /**
     * @short Y coordinate changed
     */
    void yChanged();
    /**
     * @short Z coordinate changed
     */
    void zChanged();
    /**
     * @short Width changed
     */
    void widthChanged();
    /**
     * @short Height changed
     */
    void heightChanged();
    /**
     * @short Visibility changed
     */
    void visibleChanged();
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
    WidgetProperties(WidgetPropertiesPrivate *dd, QObject *parent);
private:
    W_DECLARE_PRIVATE(WidgetProperties)
};

}

Q_DECLARE_METATYPE(Widgets::WidgetProperties *)

#endif // WIDGETS_WIDGETPROPERTIES_H
