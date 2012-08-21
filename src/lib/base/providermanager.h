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
 *
 * This provider manager is created without any provider. The status
 * of the provider should be queried through the providerStatus()
 * proerty. It is set as ProviderManager::ProviderInvalid if no provider
 * has been set. It is set as ProviderManager::ProviderUnavailable when
 * the provider is set, but still unavailable. If the provider is finally
 * available, the status is ProviderManager::ProviderAvailable.
 */
class ProviderManager: public QObject
{
    Q_OBJECT
    Q_ENUMS(ProviderStatus)
    /**
     * @short Provider status
     */
    Q_PROPERTY(ProviderStatus providerStatus READ providerStatus NOTIFY providerStatusChanged)
    /**
     * @short Provider
     */
    Q_PROPERTY(Widgets::WidgetProviderBase *provider READ provider WRITE setProvider
               NOTIFY providerChanged)
public:
    /**
     * @brief Describe provider status
     */
    enum ProviderStatus {
        /**
         * @short The provider is invalid
         */
        ProviderInvalid,
        /**
         * @short The provider is unavailable
         */
        ProviderUnavailable,
        /**
         * @short The provider is available
         */
        ProviderAvailable
    };

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
     * @brief Provider status
     * @return provider status.
     */
    ProviderStatus providerStatus() const;
    /**
     * @brief Provider
     * @return provider.
     */
    WidgetProviderBase * provider() const;
Q_SIGNALS:
    /**
     * @brief Provider status changed
     */
    void providerStatusChanged();
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
    Q_PRIVATE_SLOT(d_func(), void slotAvailable(bool available))
};

}

#endif // WIDGETS_PROVIDERMANAGER_H
