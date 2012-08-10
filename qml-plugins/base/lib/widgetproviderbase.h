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

#ifndef WIDGETPROVIDERBASE_H
#define WIDGETPROVIDERBASE_H

/**
 * @file widgetproviderbase.h
 * @short Definition of Widgets::WidgetProviderBase
 */

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "widgetbaseproperties.h"

namespace Widgets
{

class WidgetProviderBasePrivate;
/**
 * @brief Base for widget providers
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
 * - widgetName()
 * - widgetDescription()
 *
 * The first method is used to list the available
 * widgets, the second and third are used to provide
 * an absolute file path to either the widget file,
 * or the file for the configuration component associated
 * to the widget. The fourth method is used to query the
 * properties of a widget. The last two methods are used
 * to provide human readable names and descriptions of the
 * widget.
 *
 * All these methods use a disambiguation parameter, that
 * can be used to provide a hiearchy, that can represent,
 * for example, a folder hiearchy. %Widgets with the same
 * file name, but stored into two different folders can
 * be queried by passing the folder to the disambiguation
 * parameter.
 *
 * The disambiguation parameters are returned through the
 * disambiguationList() parameter. While reimplementing
 * this parameter, please make sure to at least return
 * a single element in this list.
 *
 * A provider might need some time to be loaded and available.
 * The available property is used to check the avalibility
 * of the provider. If the provider is set to be non available,
 * most process, including widget display and editing, will not
 * be available. It is up to the implementor to take care
 * of this information.
 *
 * A provider might also need to notify that it have new
 * information. The only way to do this is to set the provider
 * as unavailable first, before setting it available. Synchronous
 * providers can do this by simply setting the availabiliy to false
 * and then to true.
 *
 * Remark: this class is fully implemented due to the need
 * of an implemented class for QML metatype system. But this
 * provider do not provide anything. It should not be used.
 *
 * Remark: by default, the availibility is set to false. For
 * synchronous classes, you might need to set the availability to
 * true in the constructor.
 */
class WidgetProviderBase : public QObject
{
    Q_OBJECT
public:
    /**
     * @short If the provider is available
     */
    Q_PROPERTY(bool available READ isAvailable NOTIFY availableChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit WidgetProviderBase(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~WidgetProviderBase();
    /**
     * @brief If the provider is available
     * @return if the provider is available.
     */
    bool isAvailable() const;
    /**
     * @brief List of disambiguation parameters
     *
     * This method lists all the disambiguation parameters.
     * Disambiguations are optionnal parameters but can be
     * used to group some widgets together. By default, this
     * list returns a single element, that is an empty variant
     * hash.
     *
     * While reimplementing this method, you should make sure to
     * return at least the empty hash.
     *
     * @return a list of disambiguation parameters.
     */
    virtual QList<QVariantHash> disambiguationList() const;
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
    Q_INVOKABLE virtual QStringList
                registeredWidgets(const QVariantHash &disambiguation = QVariantHash()) const;
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
    Q_INVOKABLE virtual QString
                widgetFile(const QString &fileName,
                           const QVariantHash &disambiguation = QVariantHash()) const;
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
    Q_INVOKABLE virtual QString
                widgetSettingsFile(const QString &fileName,
                                   const QVariantHash &disambiguation = QVariantHash()) const;
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
                               const QVariantHash &disambiguation = QVariantHash());
    /**
     * @short Name of the widget
     *
     * This method is used to provide a human-readable name
     * of the widget. By default, it returns the filename.
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return name of the widget.
     */
    Q_INVOKABLE virtual QString
                widgetName(const QString &fileName,
                           const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Description
     *
     * This method is used to provide a human-readable of the
     * description of the widget. By default, it returns noting.
     *
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return description of the widget.
     */
    Q_INVOKABLE virtual QString
                widgetDescription(const QString &fileName,
                                  const QVariantHash &disambiguation = QVariantHash()) const;

Q_SIGNALS:
    /**
     * @brief Available changed
     */
    void availableChanged(bool available);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    WidgetProviderBase(WidgetProviderBasePrivate *dd, QObject *parent = 0);
    /**
     * @brief Set availability
     * @param available if the provider is available.
     */
    void setAvailable(bool available);
    /**
     * @brief D-pointer
     */
    QScopedPointer<WidgetProviderBasePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(WidgetProviderBase)
};

}

#endif // WIDGETPROVIDERBASE_H
