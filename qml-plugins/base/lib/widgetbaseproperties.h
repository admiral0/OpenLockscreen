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

#ifndef WIDGETS_WIDGETBASEPROPERTIES_H
#define WIDGETS_WIDGETBASEPROPERTIES_H

/**
 * @file widgetbaseproperties.h
 * @short Definition of Widgets::WidgetBaseProperties
 */

#include "graphicalcomponentbase.h"

#include <QtCore/QMetaType>

namespace Widgets
{

class WidgetBasePropertiesPrivate;
/**
 * @brief Base properties for widgets
 *
 * This class is used to represent all the
 * base properties that a widget have. Base
 * properties includes their inherent
 * properties that should be constant.
 *
 * These properties are all related th the expected
 * size of the widget:
 * - minimumWidth()
 * - minimumHeight()
 * - maximumWidth()
 * - maximumHeight()
 */
class WidgetBaseProperties: public GraphicalComponentBase
{
    Q_OBJECT
    /**
     * @short Minimum width
     */
    Q_PROPERTY(int minimumWidth READ minimumWidth CONSTANT)
    /**
     * @short Minimum height
     */
    Q_PROPERTY(int minimumHeight READ minimumHeight CONSTANT)
    /**
     * @short Maximum width
     */
    Q_PROPERTY(int maximumWidth READ maximumWidth CONSTANT)
    /**
     * @short Maximum height
     */
    Q_PROPERTY(int maximumHeight READ maximumHeight CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit WidgetBaseProperties(QObject *parent = 0);
    /**
     * @brief Default constructor
     *
     * @param fileName filename of the component.
     * @param disambiguation disambiguation parameter of the component.
     * @param settingsFileName filename of the settings component.
     * @param minimumWidth minimum width.
     * @param minimumHeight minimum height.
     * @param maximumWidth maximum width.
     * @param maximumHeight maximum height.
     * @param parent parent object.
     */
    explicit WidgetBaseProperties(const QString &fileName, const QVariantHash &disambiguation,
                                  const QString &settingsFileName,
                                  int minimumWidth, int minimumHeight,
                                  int maximumWidth, int maximumHeight,
                                  QObject *parent = 0);
    /**
     * @brief Minimum width
     * @return minimum width.
     */
    int minimumWidth() const;
    /**
     * @brief Minimum height
     * @return minimum width.
     */
    int minimumHeight() const;
    /**
     * @brief Maximum width
     * @return maximum width.
     */
    int maximumWidth() const;
    /**
     * @brief Maximum height
     * @return maximum height.
     */
    int maximumHeight() const;
    static WidgetBaseProperties * fromQmlFile(const QString &qmlFile,
                                              const QVariantHash &disambiguation,
                                              const QString &settingsFileName,
                                              QObject *parent = 0);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    explicit WidgetBaseProperties(WidgetBasePropertiesPrivate *dd, QObject *parent);
private:
    W_DECLARE_PRIVATE(WidgetBaseProperties)
};

}

Q_DECLARE_METATYPE(Widgets::WidgetBaseProperties *)


#endif // WIDGETS_WIDGETBASEPROPERTIES_H
