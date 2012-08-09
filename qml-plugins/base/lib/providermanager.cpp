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
     * @brief Slot for available
     *
     * This method is used to check if the provider
     * is available.
     */
    void slotAvailable();
    /**
     * @brief Provider
     */
    WidgetProviderBase *provider;
private:
    /**
     * @short Q-pointer.
     */
    ProviderManager *q_ptr;
    Q_DECLARE_PUBLIC(ProviderManager)
};

ProviderManagerPrivate::ProviderManagerPrivate(ProviderManager *q):
    provider(0), q_ptr(q)
{
}

void ProviderManagerPrivate::slotAvailable()
{
    Q_Q(ProviderManager);
    emit q->providerAvailableChanged();
}

////// End of private class //////

ProviderManager::ProviderManager(QObject *parent) :
    QObject(parent), d_ptr(new ProviderManagerPrivate(this))
{
}

ProviderManager::~ProviderManager()
{
}

bool ProviderManager::isProviderAvailable() const
{
    Q_D(const ProviderManager);
    if (!d->provider) {
        return false;
    }

    return d->provider->available();
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

        connect (d->provider, SIGNAL(availableChanged()), this, SLOT(slotAvailable()));
        d->slotAvailable();
    }
}

}

#include "moc_providermanager.cpp"
