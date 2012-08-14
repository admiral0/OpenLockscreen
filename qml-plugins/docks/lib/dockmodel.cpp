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
 * @file dockmodel.cpp
 * @short Implementation of Widgets::Docks::DockModel
 */

#include "dockmodel.h"

#include <QtCore/QList>
#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtDeclarative/QDeclarativeContext>

#include "abstractsettings_p.h"
#include "dockproperties.h"
#include "providermanager.h"
#include "mixedproviderbase.h"
#include "dockproperties_p.h"

namespace Widgets
{

namespace Docks
{

/**
 * @brief DOCK_ELEMENT
 *
 * Used in Widgets::Docks::DockModel.
 */
static const char *DOCK_ELEMENT = "dock";

/**
 * @internal
 * @short Private class for Widgets::Docks::DockModelPrivate
 */
class DockModelPrivate: public AbstractSettings
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    DockModelPrivate(DockModel *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~DockModelPrivate();
    /**
     * @internal
     * @brief Refresh the provider
     *
     * This method is called when the provider has changed.
     * It tries to cast the provider to the correct form
     * and reload the settings.
     */
    void refreshProvider();
    /**
     * @internal
     * @brief Clear
     */
    virtual void clear();
    /**
     * @internal
     * @brief Load from XML element
     *
     * @param element the source XML element.
     * @return if the loading succeded.
     */
    virtual bool fromXmlElement(const QDomElement &element);
    /**
     * @internal
     * @brief Save to XML element
     *
     * @param tagName the tag that will be used to create this element.
     * @param document a pointer to the document that is used to create elements.
     * @return the class as an XML element.
     */
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    /**
     * @internal
     * @short Data
     */
    QList<DockProperties *> data;
    /**
     * @internal
     * @short Provider manager
     */
    ProviderManager *providerManager;
    /**
     * @internal
     * @short Provider
     */
    MixedProviderBase *provider;
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    DockModel * const q_ptr;
    Q_DECLARE_PUBLIC(DockModel)
};

DockModelPrivate::DockModelPrivate(DockModel *q):
    AbstractSettings(q), q_ptr(q)
{
    componentName = "dock";
    providerManager = 0;
}

DockModelPrivate::~DockModelPrivate()
{
    clear();
}

void DockModelPrivate::refreshProvider()
{
    provider = 0;
    Q_Q(DockModel);
    if (!providerManager) {
        return;
    }

    WidgetProviderBase *widgetProvider = providerManager->provider();
    MixedProviderBase *mixedProvider = static_cast<MixedProviderBase *>(widgetProvider);
    if (!mixedProvider) {
        return;
    }
    provider = mixedProvider;
    q->load();
}

void DockModelPrivate::clear()
{
    Q_Q(DockModel);
    q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
    q->endRemoveRows();
}

bool DockModelPrivate::fromXmlElement(const QDomElement &element)
{
    Q_Q(DockModel);
    if (element.tagName() != SETTINGS_ELEMENT) {
        return false;
    }

    DockPropertiesComponentBuilder *builder = new DockPropertiesComponentBuilder();
    BuildManager<DockProperties *> *buildManager = new BuildManager<DockProperties *>();
    buildManager->setBuilder(builder);


    QDomElement dockElement = element.firstChildElement(DOCK_ELEMENT);
    while (!dockElement.isNull()) {
        builder->setProperties(dockElement, q);
        DockBaseProperties *base = provider->dock(builder->fileName(),
                                                  builder->disambiguation());
        if (base) {
            builder->setDockBaseProperties(base);
            buildManager->build();

            q->addDock(buildManager->element());
            base->deleteLater();
        }
        dockElement = dockElement.nextSiblingElement(DOCK_ELEMENT);
    }

    return true;
}

QDomElement DockModelPrivate::toXmlElement(const QString &tagName, QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);

    DockPropertiesXmlBuilder *builder = new DockPropertiesXmlBuilder();
    BuildManager<QDomElement> *buildManager = new BuildManager<QDomElement>();
    buildManager->setBuilder(builder);


    foreach(DockProperties *dock, data) {
        builder->setProperties(dock, DOCK_ELEMENT, document);
        buildManager->build();
        element.appendChild(buildManager->element());
    }

    return element;
}

////// End of private class //////

DockModel::DockModel(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new DockModelPrivate(this))
{
    QHash <int, QByteArray> roles;
    roles.insert(DockRole, "dock");
    setRoleNames(roles);
}

DockModel::DockModel(DockModelPrivate *dd, QObject *parent):
    QAbstractListModel(parent), d_ptr(dd)
{
    QHash <int, QByteArray> roles;
    roles.insert(DockRole, "dock");
    setRoleNames(roles);
}

DockModel::~DockModel()
{
}

void DockModel::setProviderManager(ProviderManager *providerManager)
{
    Q_D(DockModel);
    if (d->providerManager != providerManager) {
        d->providerManager = providerManager;

        connect(d->providerManager, SIGNAL(providerStatusChanged()), this, SLOT(refreshProvider()));
        d->refreshProvider();
    }
}

int DockModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const DockModel);
    return d->data.count();
}

int DockModel::count() const
{
    return rowCount();
}

QVariant DockModel::data(const QModelIndex &index, int role) const
{
    Q_D(const DockModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    DockProperties *dock = d->data.at(row);
    switch(role) {
    case DockRole:
        return QVariant::fromValue(dock);
        break;
    default:
        return QVariant();
    }
}

bool DockModel::hasDock(const QString &fileName, const QVariantMap &disambiguation) const
{
    Q_D(const DockModel);
    bool added = false;
    QListIterator<DockProperties *> iterator = QListIterator<DockProperties *>(d->data);
    while (!added && iterator.hasNext()) {
        DockProperties *addedDock = iterator.next();
        if (disambiguation == addedDock->disambiguation() &&
            fileName == addedDock->fileName()) {
            added = true;
        }
    }

    return added;
}

void DockModel::load()
{
    Q_D(DockModel);
    if (!d->provider) {
        return;
    }

    if (!d->provider->isAvailable()) {
        return;
    }

    d->load();
}

void DockModel::addDock(DockBaseProperties *dock, const QVariantMap &settings,
                        const QString &identifier)
{
    if(dock == 0) {
        return;
    }

    DockProperties *newDock;
    if (identifier.isEmpty()) {
        newDock = new DockProperties(dock, settings, this);
    } else {
        newDock = new DockProperties(dock, identifier, settings, this);
    }

    addDock(newDock);
}

void DockModel::addDock(DockProperties *dock)
{
    Q_D(DockModel);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    d->data.append(dock);
    emit countChanged(rowCount());
    endInsertRows();

    d->requestSave();
}

void DockModel::removeDock(DockProperties *dock)
{
    Q_D(DockModel);

    int index = d->data.indexOf(dock);
    if (index == -1) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);

    d->data.takeAt(index)->deleteLater();

    emit countChanged(rowCount());
    endRemoveRows();

    d->requestSave();
}

bool DockModel::event(QEvent *event)
{
    Q_D(DockModel);
    if (event->type() == QEvent::UpdateRequest) {
        d->save();
        return true;
    }
    return QObject::event(event);
}

}

}

#include "moc_dockmodel.cpp"
