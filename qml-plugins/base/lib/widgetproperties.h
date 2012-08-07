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

#include "widgetbaseproperties.h"

#include <QtCore/QMetaType>
#include <QtCore/QVariantMap>

#include "identifiedelementinterface.h"

namespace Widgets
{

class WidgetPropertiesPrivate;
class WidgetProperties: public WidgetBaseProperties, private IdentifiedElementInterface
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier NOTIFY identifierChanged)
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
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QVariantMap settings READ settings WRITE setSettings NOTIFY settingsChanged)
public:
    explicit WidgetProperties(QObject *parent = 0);
    explicit WidgetProperties(WidgetBaseProperties *base,
                              int x, int y, int z, int width, int height,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    explicit WidgetProperties(WidgetBaseProperties *base,
                              const QRect &geometry, int z,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    explicit WidgetProperties(WidgetBaseProperties *base,
                              const QString &identifier,
                              int x, int y, int z, int width, int height,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    explicit WidgetProperties(WidgetBaseProperties *base,
                              const QRect &geometry, int z,
                              const QString &identifier,
                              const QVariantMap &settings = QVariantMap(),
                              QObject *parent = 0);
    QString identifier() const;
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
    bool isVisible() const;
    QVariantMap settings() const;
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
Q_SIGNALS:
    void identifierChanged(const QString &identifier);
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
    void visibleChanged(bool visible);
    /**
     * @short Settings changed
     *
     * Notify that the settings has
     * changed.
     *
     * @param settings value of the new settings.
     */
    void settingsChanged(const QVariantMap &settings);
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
    void setVisible(bool visible);
    /**
     * @short Set the settings that belongs to this widget
     *
     * This method is used to set the
     * settings that belongs to this widget.
     *
     * @param settings settings to set.
     */
    void setSettings(const QVariantMap &settings);
protected:
    WidgetProperties(WidgetPropertiesPrivate *dd, QObject *parent);
    void setIdentifier(const QString &identifier);
private:
    W_DECLARE_PRIVATE(WidgetProperties)
};

}

Q_DECLARE_METATYPE(Widgets::WidgetProperties *)

#endif // WIDGETS_WIDGETPROPERTIES_H
