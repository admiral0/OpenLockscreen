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
 * @file widgetproperties.h
 * @short Definition of Widgets::WidgetProperties
 *
 * This file contains the definition of the
 * Widgets::WidgetProperties class.
 */

#ifndef WIDGETS_WIDGETPROPERTIES_H
#define WIDGETS_WIDGETPROPERTIES_H

#include <QtCore/QMetaType>
#include <QtCore/QVariantMap>

#include "widgetbaseproperties.h"
#include "identifiedelementinterface.h"
#include "elementsettings.h"

namespace Widgets
{

/**
 * @short Properties for a displayed widget
 *
 * This class is used to store properties
 * for a widget that is displayed.
 *
 * This class stores these properties
 * - widget's position and size
 * - identifier of the widget
 * - settings specific to this widget
 *
 * Each of these properties can be access
 * either using getter methods or using
 * properties, in a QML context.
 *
 * This class is used for managing displayed
 * widgets : the displayed widgets are usually
 * not moved by the user, but moved because of
 * the properties of this object changed.
 */
class WidgetProperties: public WidgetBaseProperties, private IdentifiedElementInterface
{
    Q_OBJECT
    /**
     * @short Current x coordinate of the widget
     */
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    /**
     * @short Current y coordinate of the widget
     */
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    /**
     * @short Current z coordinate of the widget
     */
    Q_PROPERTY(int z READ z WRITE setZ NOTIFY zChanged)
    /**
     * @short Current width of the widget
     */
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    /**
     * @short Current height of the widget
     */
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
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
     * widget properties with no property. It is used for QML type
     * implementation.
     *
     * @param parent parent object.
     */
    explicit WidgetProperties(QObject *parent = 0);
    /**
     * @short Default constructor
     *
     * This constructor is used to create a widget
     * properties containing all the needed properties
     * and an auto-generated identifier.
     *
     * @param name name of the widget.
     * @param defaultWidth default width of the widget.
     * @param defaultHeight default height of the widget.
     * @param qmlFile QML file used to create the widget.
     * @param package package which the widget belongs to.
     * @param hasSettings if the widget has settings.
     * @param x x coordinate of the widget.
     * @param y y coordinate of the widget.
     * @param z z coordinate of the widget.
     * @param width width of the widget.
     * @param height height of the widget.
     * @param settings settings that belongs to the widget.
     * @param parent parent object.
     */
    explicit WidgetProperties(const QString &name,
                              int defaultWidth,
                              int defaultHeight,
                              const QString &qmlFile,
                              const QString &package,
                              bool hasSettings,
                              int x,
                              int y,
                              int z,
                              int width,
                              int height,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    /**
     * @short Overloaded constructor
     *
     * This constructor is used to create a widget
     * properties containing all the needed properties
     * while setting the identifier.
     *
     * @param name name of the widget.
     * @param defaultWidth default width of the widget.
     * @param defaultHeight default height of the widget.
     * @param qmlFile QML file used to create the widget.
     * @param package package which the widget belongs to.
     * @param hasSettings if the widget has settings.
     * @param identifier identifier of the widget.
     * @param x x coordinate of the widget.
     * @param y y coordinate of the widget.
     * @param z z coordinate of the widget.
     * @param width width of the widget.
     * @param height height of the widget.
     * @param settings settings that belongs to the widget.
     * @param parent parent object.
     */
    explicit WidgetProperties(const QString &name,
                              int defaultWidth,
                              int defaultHeight,
                              const QString &qmlFile,
                              const QString &package,
                              bool hasSettings,
                              const QString &identifier,
                              int x,
                              int y,
                              int z,
                              int width,
                              int height,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~WidgetProperties();
    /**
     * @short Current x coordinate of the widget
     *
     * This method is used to retrieve the current
     * x coordinate of the widget.
     *
     * @return current x coordinate of the widget.
     */
    int x() const;
    /**
     * @short Current y coordinate of the widget
     *
     * This method is used to retrieve the current
     * y coordinate of the widget.
     *
     * @return current y coordinate of the widget.
     */
    int y() const;
    /**
     * @short Current z coordinate of the widget
     *
     * This method is used to retrieve the current
     * z coordinate of the widget.
     *
     * @return current z coordinate of the widget.
     */
    int z() const;
    /**
     * @short Current width of the widget
     *
     * This method is used to retrieve the current
     * width of the widget.
     *
     * @return current width of the widget.
     */
    int width() const;
    /**
     * @short Current height of the widget
     *
     * This method is used to retrieve the current
     * height of the widget.
     *
     * @return current height of the widget.
     */
    int height() const;
    /**
     * @short Identifier
     *
     * This method is used to retrieve the identifier
     * that is used to uniquely identify this widget.
     *
     * @return this widget's identifier.
     */
    QString identifier() const;
    /**
     * @short Settings that belongs to this widget
     *
     * This method is used to retrieve the settings
     * that belongs to this widget.
     *
     * @return settings that belongs to this widget.
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
     * @short X coordinate changed
     *
     * Notify that the current x coordinate
     * has changed.
     *
     * @param x value of the new x coordinate.
     */
    void xChanged(int x);
     /**
     * @short y coordinate changed
     *
     * Notify that the current y coordinate
     * has changed.
     *
     * @param y value of the new y coordinate.
     */
    void yChanged(int y);
     /**
     * @short Z coordinate changed
     *
     * Notify that the current z coordinate
     * has changed.
     *
     * @param z value of the new z coordinate.
     */
    void zChanged(int z);
     /**
     * @short Width changed
     *
     * Notify that the current width
     * has changed.
     *
     * @param width value of the new width.
     */
    void widthChanged(int width);
    /**
     * @short Height changed
     *
     * Notify that the current height
     * has changed.
     *
     * @param height value of the new height.
     */
    void heightChanged(int height);
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
     * @short Set the x coordinate of the widget
     *
     * This method is used to set the
     * x coordinate of the widget.
     *
     * @param x x coordinate to set.
     */
    void setX(int x);
    /**
     * @short Set the y coordinate of the widget
     *
     * This method is used to set the
     * y coordinate of the widget.
     *
     * @param y y coordinate to set.
     */
    void setY(int y);
    /**
     * @short Set the z coordinate of the widget
     *
     * This method is used to set the
     * z coordinate of the widget.
     *
     * @param z z coordinate to set.
     */
    void setZ(int z);
    /**
     * @short Set the width of the widget
     *
     * This method is used to set the
     * width of the widget.
     *
     * @param width width to set.
     */
    void setWidth(int width);
    /**
     * @short Set the height of the widget
     *
     * This method is used to set the
     * height of the widget.
     *
     * @param height height to set.
     */
    void setHeight(int height);
    /**
     * @short Set the settings that belongs to this widget
     *
     * This method is used to set the
     * settings that belongs to this widget.
     *
     * @param settings settings to set.
     */
    void setSettings(const QVariantMap &settings);
private:
    class WidgetPropertiesPrivate;
    /**
     * @short D-pointer
     */
    WidgetPropertiesPrivate *const d;
};

}

Q_DECLARE_METATYPE(Widgets::WidgetProperties*)

#endif // WIDGETS_WIDGETPROPERTIES_H
