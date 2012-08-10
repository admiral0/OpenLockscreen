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

#ifndef WIDGETS_PROVIDER_BASIC_BASICPROVIDER_H
#define WIDGETS_PROVIDER_BASIC_BASICPROVIDER_H

/**
 * @file basicwidgetprovider.h
 * @short Definition of Widgets::Provider::Basic::BasicWidgetProvider
 */

#include "widgetproviderbase.h"


namespace Widgets
{

namespace Provider
{

namespace Basic
{

class BasicWidgetProviderPrivate;

/**
 * @brief A basic widget provider
 *
 * This provider is a very basic provider that
 * is used to retrieve widgets from a folder.
 *
 * The page about \ref pluginProviderBasic "basic providers"
 * provides details on how to use this class.
 */
class BasicWidgetProvider: public WidgetProviderBase
{
    Q_OBJECT
    /**
     * @short Path to search for widgets
     */
    Q_PROPERTY(QString widgetsPath READ widgetsPath WRITE setWidgetsPath
               NOTIFY widgetsPathChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit BasicWidgetProvider(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~BasicWidgetProvider();
    /**
     * @brief Path to search for widgets
     * @return path to search for widgets.
     */
    QString widgetsPath() const;
    /**
     * @short Registered widgets
     *
     * @param disambiguation disambiguation parameter.
     * @return a list of registered widgets.
     */
    Q_INVOKABLE virtual QStringList
                registeredWidgets(const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Absolute path to the widget file
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
     * @param fileName the widget filename.
     * @param disambiguation disambiguation parameter.
     * @return widget properties.
     */
    Q_INVOKABLE virtual Widgets::WidgetBaseProperties *
                        widget(const QString &fileName,
                               const QVariantHash &disambiguation = QVariantHash());
public Q_SLOTS:
    /**
     * @brief Set the path to search for widgets
     * @param widgetsPath path to search for widgets.
     */
    void setWidgetsPath(const QString &widgetsPath);
Q_SIGNALS:
    /**
     * @brief The path to search for widgets changed
     */
    void widgetsPathChanged();
private:
    Q_DECLARE_PRIVATE(BasicWidgetProvider)
};

}

}

}

#endif // WIDGETS_PROVIDER_BASIC_BASICPROVIDER_H
