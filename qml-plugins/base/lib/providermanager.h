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

#ifndef WIDGETS_PROVIDERMANAGER_H
#define WIDGETS_PROVIDERMANAGER_H

/**
 * @file providermanager.h
 * @short Definition of Widgets::ProviderManager
 */

#include <QtCore/QObject>

#include "widgetproviderbase.h"

namespace Widgets
{

class ProviderManagerPrivate;

/**
 * @brief Provider manager
 *
 * The provider manager is used manage widget providers.
 * It simply provide a property that can be accessed through QML,
 * though providing a way to set a custom provider from QML.
 */
class ProviderManager: public QObject
{
    Q_OBJECT
    /**
     * @short Provider available
     */
    Q_PROPERTY(bool providerAvailable READ isProviderAvailable NOTIFY providerAvailableChanged)
    /**
     * @short Provider
     */
    Q_PROPERTY(Widgets::WidgetProviderBase *provider READ provider WRITE setProvider
               NOTIFY providerChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit ProviderManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~ProviderManager();
    /**
     * @brief If the provider is available
     * @return if the provider is available.
     */
    bool isProviderAvailable() const;
    /**
     * @brief Provider
     * @return provider.
     */
    WidgetProviderBase * provider() const;
Q_SIGNALS:
    /**
     * @brief Provider availability changed
     */
    void providerAvailableChanged();
    /**
     * @brief Provider changed
     */
    void providerChanged();
public Q_SLOTS:
    /**
     * @brief Set provider.
     * @param provider provider.
     */
    void setProvider(Widgets::WidgetProviderBase *provider);
protected:
    /**
     * @brief D-pointer
     */
    QScopedArrayPointer<ProviderManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(ProviderManager)
    Q_PRIVATE_SLOT(d_func(), void slotAvailable())
};

}

#endif // WIDGETS_PROVIDERMANAGER_H
