/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef WIDGETS_WIDGETPROVIDERINTERFACE_H
#define WIDGETS_WIDGETPROVIDERINTERFACE_H

/**
 * @file widgetproviderinterface.h
 * @short Definition of Widgets::WidgetProviderInterface
 */

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QVariantHash>

namespace Widgets
{

class WidgetBaseProperties;
/**
 * @brief Interface for widget providers
 *
 * Component widget are classes that are used to
 * provide path and information about a widget
 * that will be registered in a widget models.
 *
 * This interface is a common interface for
 * these providers, that should provide these
 * common methods
 *
 * - registeredWidgets()
 * - widgetFile()
 * - widgetSettingsFile()
 * - widget()
 *
 * The first method is used to list the available
 * widgets, the second and third are used to provide
 * an absolute file path to either the widget file,
 * or the file for the configuration component associated
 * to the widget. The last method is used to query the
 * properties of a widget.
 *
 * All these methods use a disambiguation parameter, that
 * can be used to provide a hiearchy, that can represent,
 * for example, a folder hiearchy. %Widgets with the same
 * file name, but stored into two different folders can
 * be queried by passing the folder to the disambiguation
 * parameter.
 *
 * The use of disambiguation parameter is up to the
 * implementor.
 */
class WidgetProviderInterface: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Destructor
     */
    virtual ~WidgetProviderInterface() {};
    /**
     * @short Registered widgets
     *
     * This method lists all the available widgets for
     * a given disambiguation parameter. The list contains
     * the widget filename.
     *
     * @param disambiguation disambiguation parameter.
     * @return a list of registered widgets.
     */
    Q_INVOKABLE virtual QStringList registeredWidgets(const QVariantHash &disambiguation) const = 0;
    /**
     * @short Absolute path to the widget file
     *
     * This method is used to provide the absolute path to
     * the widget file, given the filename and a
     * disambiguation parameter.
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the widget file.
     */
    Q_INVOKABLE virtual QString widgetFile(const QString &fileName,
                                           const QVariantHash &disambiguation) const = 0;
    /**
     * @short Absolute path to the widget configuration component file
     *
     * This method is used to provide the absolute path to
     * the configuration component file, associated to a
     * widget, given the filename of this widget and a
     * disambiguation parameter.
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the widget configuration component file.
     */
    Q_INVOKABLE virtual QString widgetSettingsFile(const QString &fileName,
                                                   const QVariantHash &disambiguation) const = 0;
    /**
     * @short Widget properties
     *
     * This method is used to provide properties
     * of a widget, given the filename and a
     * disambiguation parameter.
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return widget properties.
     */
    Q_INVOKABLE virtual Widgets::WidgetBaseProperties *
                        widget(const QString &fileName,
                               const QVariantHash &disambiguation) const = 0;
};

}

#endif // WIDGETS_WIDGETPROVIDERINTERFACE_H
