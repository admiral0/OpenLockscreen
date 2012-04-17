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

#include "dockproperties.h"
#include "dockproperties_p.h"
#include "dockpropertiesdefines.h"

namespace Widgets
{

DockProperties::DockProperties(QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate, parent)
{
}

DockProperties::DockProperties(const QString &fileName, const QString &packageIdentifier,
                               bool settingsEnabled,
                               int width, int height,
                               bool anchorsTop, bool anchorsBottom,
                               bool anchorsLeft, bool anchorsRight,
                               const QVariantMap &settings, QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate, parent)
{
    Q_D(DockProperties);
    d->fileName = fileName;
    d->packageIdentifier = packageIdentifier;
    d->settingsEnabled = settingsEnabled;
    d->size = QSize(width, height);
    d->anchorsTop = anchorsTop;
    d->anchorsBottom = anchorsBottom;
    d->anchorsLeft = anchorsLeft;
    d->anchorsRight = anchorsRight;
    d->identifier = generateIdentifier();
    d->settings = settings;
}

DockProperties::DockProperties(const QString &fileName, const QString &packageIdentifier,
                               bool settingsEnabled,
                               int width, int height,
                               bool anchorsTop, bool anchorsBottom,
                               bool anchorsLeft, bool anchorsRight,
                               const QString &identifier, const QVariantMap &settings,
                               QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate, parent)
{
    Q_D(DockProperties);
    d->fileName = fileName;
    d->packageIdentifier = packageIdentifier;
    d->settingsEnabled = settingsEnabled;
    d->size = QSize(width, height);
    d->anchorsTop = anchorsTop;
    d->anchorsBottom = anchorsBottom;
    d->anchorsLeft = anchorsLeft;
    d->anchorsRight = anchorsRight;
    d->identifier = identifier;
    d->settings = settings;
}

DockProperties::DockProperties(DockPropertiesPrivate *dd, QObject *parent):
    DockBaseProperties(dd, parent)
{
}

QString DockProperties::identifier() const
{
    Q_D(const DockProperties);
    return d->identifier;
}

QVariantMap DockProperties::settings() const
{
    Q_D(const DockProperties);
    return d->settings;
}

bool DockProperties::fromXmlElement(const QDomElement &element)
{
    if (!element.hasAttribute(DOCK_PROPERTIES_IDENTIFIER_ATTRIBUTE)) {
        return false;
    }
    QDomElement settingsElement = element.firstChildElement(DOCK_PROPERTIES_SETTINGS_TAGNAME);
    if (settingsElement.isNull()) {
        return false;
    }

    if (!DockBaseProperties::fromXmlElement(element)) {
        return false;
    }

    setIdentifier(element.attribute(DOCK_PROPERTIES_IDENTIFIER_ATTRIBUTE));

    QVariantMap settings;
    QDomElement property =
            settingsElement.firstChildElement(DOCK_PROPERTIES_SETTINGS_ENTRY_TAGNAME);
    while (!property.isNull()) {
        QString key = property.attribute(DOCK_PROPERTIES_SETTINGS_KEY_ATTRIBUTE);
        QString value = property.attribute(DOCK_PROPERTIES_SETTINGS_VALUE_ATTRIBUTE);

        settings.insert(key, QVariant(value));
    }
    return true;
}

QDomElement DockProperties::toXmlElement(const QString &tagName, QDomDocument *document) const
{
    QDomElement element = DockBaseProperties::toXmlElement(tagName, document);
    element.setAttribute(DOCK_PROPERTIES_IDENTIFIER_ATTRIBUTE, identifier());

    QDomElement settingsElement = document->createElement(DOCK_PROPERTIES_SETTINGS_TAGNAME);
    QMapIterator<QString, QVariant> settingsIterator = QMapIterator<QString, QVariant>(settings());
    while (settingsIterator.hasNext()) {
        settingsIterator.next();
        QDomElement settingsEntryElement =
                document->createElement(DOCK_PROPERTIES_SETTINGS_ENTRY_TAGNAME);
        settingsEntryElement.setAttribute(DOCK_PROPERTIES_SETTINGS_KEY_ATTRIBUTE,
                                          settingsIterator.key());
        settingsEntryElement.setAttribute(DOCK_PROPERTIES_SETTINGS_VALUE_ATTRIBUTE,
                                          settingsIterator.value().toString());
        settingsElement.appendChild(settingsEntryElement);
    }
    element.appendChild(settingsElement);

    return element;
}


void DockProperties::setSettings(const QVariantMap &settings)
{
    Q_D(DockProperties);
    if (d->settings != settings) {
        d->settings = settings;
        emit settingsChanged(settings);
    }
}

void DockProperties::setIdentifier(const QString &identifier)
{
    Q_D(DockProperties);
    if (d->identifier != identifier) {
        d->identifier = identifier;
        emit identifierChanged(identifier);
    }
}


}
