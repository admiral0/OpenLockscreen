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

/**
 * @file providermanager.cpp
 * @short Implementation of Widgets::ProviderManager
 */

#include "providermanager.h"
#include <QtCore/QDebug>

namespace Widgets
{

/**
 * @internal
 * @brief Private class for Widgets::ProviderManager
 */
class ProviderManagerPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    explicit ProviderManagerPrivate(ProviderManager *q);
    /**
     * @internal
     * @brief Slot for available
     *
     * This method is used to check if the provider
     * is available.
     *
     * @param available if the provider is available.
     */
    void slotAvailable(bool available);
    /**
     * @internal
     * @brief Set status
     * @param status status to set.
     */
    void setStatus(ProviderManager::ProviderStatus status);
    /**
     * @internal
     * @brief Provider
     */
    WidgetProviderBase *provider;
    /**
     * @internal
     * @brief Provider status
     */
    ProviderManager::ProviderStatus status;
private:
    /**
     * @internal
     * @short Q-pointer.
     */
    ProviderManager *q_ptr;
    Q_DECLARE_PUBLIC(ProviderManager)
};

ProviderManagerPrivate::ProviderManagerPrivate(ProviderManager *q):
    provider(0), q_ptr(q)
{
    status = ProviderManager::ProviderInvalid;
}

void ProviderManagerPrivate::slotAvailable(bool available)
{
    if (available) {
        setStatus(ProviderManager::ProviderAvailable);
    } else {
        setStatus(ProviderManager::ProviderUnavailable);
    }
}

void ProviderManagerPrivate::setStatus(ProviderManager::ProviderStatus statusToSet)
{
    Q_Q(ProviderManager);
    if (status != statusToSet) {
        status = statusToSet;
        emit q->providerStatusChanged();
    }
}

////// End of private class //////

ProviderManager::ProviderManager(QObject *parent) :
    QObject(parent), d_ptr(new ProviderManagerPrivate(this))
{
}

ProviderManager::~ProviderManager()
{
}

ProviderManager::ProviderStatus ProviderManager::providerStatus() const
{
    Q_D(const ProviderManager);
    return d->status;
}

WidgetProviderBase * ProviderManager::provider() const
{
    Q_D(const ProviderManager);
    return d->provider;
}

void ProviderManager::setProvider(WidgetProviderBase *provider)
{
    Q_D(ProviderManager);
    if (d->provider != provider) {
        d->provider = provider;
        emit providerChanged();

        connect (d->provider, SIGNAL(availableChanged(bool)), this, SLOT(slotAvailable(bool)));
        if (d->provider->isAvailable()) {
            d->setStatus(ProviderManager::ProviderAvailable);
        } else {
            d->setStatus(ProviderManager::ProviderUnavailable);
        }
        d->slotAvailable(d->provider->isAvailable());
    }
}

}

#include "moc_providermanager.cpp"
