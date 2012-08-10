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

#ifndef WIDGETS_PROVIDER_BASIC_MIXEDPROVIDER_H
#define WIDGETS_PROVIDER_BASIC_MIXEDPROVIDER_H

/**
 * @file basicmixedprovider.h
 * @short Definition of Widgets::Provider::Basic::BasicMixedProvider
 */

#include "mixedproviderbase.h"

namespace Widgets
{

namespace Provider
{

namespace Basic
{

class BasicMixedProviderPrivate;

/**
 * @brief A basic mixed provider
 *
 * This provider is a very basic provider that
 * is used to retrieve widgets and docks from a folder.
 *
 * The page about \ref pluginProviderBasic "basic providers"
 * provides details on how to use this class.
 */
class BasicMixedProvider: public Docks::MixedProviderBase
{
    Q_OBJECT
    /**
     * @short Path to search for widgets
     */
    Q_PROPERTY(QString widgetsPath READ widgetsPath WRITE setWidgetsPath
               NOTIFY widgetsPathChanged)
    /**
     * @short Path to search for docks
     */
    Q_PROPERTY(QString docksPath READ docksPath WRITE setDocksPath NOTIFY docksPathChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit BasicMixedProvider(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~BasicMixedProvider();
    /**
     * @brief Path to search for widgets
     * @return path to search for widgets.
     */
    QString widgetsPath() const;
    /**
     * @brief Path to search for docks
     * @return path to search for docks.
     */
    QString docksPath() const;
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
    /**
     * @short Registered docks
     *
     * @param disambiguation disambiguation parameter.
     * @return a list of registered docks.
     */
    Q_INVOKABLE virtual QStringList
                registeredDocks(const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Absolute path to the dock file
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the dock file.
     */
    Q_INVOKABLE virtual QString
                dockFile(const QString &fileName,
                         const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Absolute path to the dock configuration component file
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return absolute path to the dock configuration component file.
     */
    Q_INVOKABLE virtual QString
                dockSettingsFile(const QString &fileName,
                                 const QVariantHash &disambiguation = QVariantHash()) const;
    /**
     * @short Dock properties
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return dock properties.
     */
    Q_INVOKABLE virtual Widgets::Docks::DockBaseProperties *
                        dock(const QString &fileName,
                             const QVariantHash &disambiguation = QVariantHash());
public Q_SLOTS:
    /**
     * @brief Set the path to search for widgets
     * @param widgetsPath path to search for widgets.
     */
    void setWidgetsPath(const QString &widgetsPath);
    /**
     * @brief Set the path to search for docks
     * @param docksPath path to search for docks.
     */
    void setDocksPath(const QString &docksPath);
Q_SIGNALS:
    /**
     * @brief The path to search for widgets changed
     */
    void widgetsPathChanged();
    /**
     * @brief The path to search for docks changed
     */
    void docksPathChanged();
private:
    Q_DECLARE_PRIVATE(BasicMixedProvider)
};

}

}

}

#endif // WIDGETS_PROVIDER_BASIC_MIXEDPROVIDER_H
