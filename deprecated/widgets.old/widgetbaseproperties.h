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
 * @file widgetbaseproperties.h
 * @short Definition of Widgets::WidgetBaseProperties
 *
 * This file contains the definition of the
 * Widgets::WidgetBaseProperties class.
 */

#ifndef WIDGETS_WIDGETBASEPROPERTIES_H
#define WIDGETS_WIDGETBASEPROPERTIES_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include "mappableelementinterface.h"

namespace Widgets
{

/**
 * @short Base properties for a widget
 *
 * This class is used to store properties
 * for a widget that is not created yet.
 *
 * This class stores these properties
 * - name of the widget
 * - widget's default width and height
 * - package where the widget is from and file to create it
 * - if the widget has settings
 * 
 * Remark : the QML file used to create the
 * widget is provided as an absolute path.
 *
 * Each of these properties can be access
 * either using getter methods or using
 * properties, in a QML context.
 *
 * Please note that all the properties
 * are constant and they should be passed
 * through the constructor.
 *
 * @see widgetsCreation
 */
class WidgetBaseProperties: public QObject, public MappableElementInterface
{
    Q_OBJECT
    /**
     * @short Name of the widget
     */
    Q_PROPERTY(QString name READ name CONSTANT)
    /**
     * @short Default width of the widget
     */
    Q_PROPERTY(int defaultWidth READ defaultWidth CONSTANT)
    /**
     * @short Default height of the widget
     */
    Q_PROPERTY(int defaultHeight READ defaultHeight CONSTANT)
    /**
     * @short QML file used to create the widget
     */
    Q_PROPERTY(QString qmlFile READ qmlFile CONSTANT)
    /**
     * @short Package which the widget belongs to
     */
    Q_PROPERTY(QString package READ package CONSTANT)
    /**
     * @short If the widget has settings
     */
    Q_PROPERTY(bool hasSettings READ hasSettings CONSTANT)
public:
    /**
     * @short Invalid constructor
     *
     * This constructor is not used and creates an empty
     * widget base properties with no property. It is used for QML type
     * implementation.
     *
     * @param parent parent object.
     */
    explicit WidgetBaseProperties(QObject *parent = 0);
    /**
     * @short Default constructor
     *
     * This constructor is used to create a widget base
     * properties containing all the needed properties.
     *
     * @param name name of the widget.
     * @param defaultWidth default width of the widget.
     * @param defaultHeight default height of the widget.
     * @param qmlFile QML file used to create the widget.
     * @param package package which the widget belongs to.
     * @param hasSettings if the widget has settings.
     * @param parent parent object.
     */
    explicit WidgetBaseProperties(const QString &name,
                                  int defaultWidth,
                                  int defaultHeight,
                                  const QString &qmlFile,
                                  const QString &package = QString(),
                                  bool hasSettings = false,
                                  QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~WidgetBaseProperties();
    /**
     * @short Name of the widget
     *
     * This method is used to retrieve the name of
     * the widget.
     *
     * @return name of the widget.
     */
    QString name() const;
     /**
     * @short Default width of the widget
     *
     * This method is used to retrieve the default
     * width of the widget.
     *
     * @return default width of the widget.
     */
    int defaultWidth() const;
     /**
     * @short Default height of the widget
     *
     * This method is used to retrieve the default
     * height of the widget.
     *
     * @return default height of the widget.
     */
    int defaultHeight() const;
    /**
     * @short QML file used to create the widget
     *
     * This method is used to retrieve the QML file
     * used to create the widget.
     *
     * @return QML file used to create the widget.
     */
    QString qmlFile() const;
    /**
     * @short Package which the widget belongs to
     *
     * This method is used to retrieve the package
     * which the widget belongs to.
     *
     * @return package which the widget belongs to.
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
    class WidgetBasePropertiesPrivate;
    /**
     * @short D-pointer
     */
    WidgetBasePropertiesPrivate * const d;
};

}

Q_DECLARE_METATYPE(Widgets::WidgetBaseProperties*)

#endif // WIDGETS_WIDGETBASEPROPERTIES_H
