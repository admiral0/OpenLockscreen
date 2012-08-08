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
#include "dockbaseproperties_p.h"
#include "graphicalcomponent_p.h"

namespace Widgets
{

static const char *DOCK_PROPERTIES_SETTINGS_TAGNAME = "settings";
static const char *DOCK_PROPERTIES_SETTINGS_ENTRY_TAGNAME = "entry";
static const char *DOCK_PROPERTIES_SETTINGS_KEY_ATTRIBUTE = "key";
static const char *DOCK_PROPERTIES_SETTINGS_VALUE_ATTRIBUTE = "value";
static const char *DOCK_PROPERTIES_IDENTIFIER_ATTRIBUTE = "identifier";

class DockPropertiesPrivate: public DockBasePropertiesPrivate, public GraphicalComponentPrivate
{
public:
    DockPropertiesPrivate(DockProperties *q);

    void copyFromBase(DockBaseProperties *base);

private:
    Q_DECLARE_PUBLIC(DockProperties)
};

DockPropertiesPrivate::DockPropertiesPrivate(DockProperties *q):
    DockBasePropertiesPrivate(q), GraphicalComponentPrivate()
{
}

void DockPropertiesPrivate::copyFromBase(DockBaseProperties *base)
{
    icon = base->icon();
    defaultName = base->defaultName();
    defaultDescription = base->defaultDescription();
    foreach (QString language, base->languages()) {
        QPair <QString, QString> data;
        data.first = base->name(language);
        data.second = base->description(language);
        nameAndDescription.insert(language, data);
    }


    fileName = base->fileName();
    packageIdentifier = base->packageIdentifier();
    settingsFileName = base->settingsFileName();
    size = QSize(base->width(), base->height());
    anchorsTop = base->anchorsTop();
    anchorsBottom = base->anchorsBottom();
    anchorsLeft = base->anchorsLeft();
    anchorsRight = base->anchorsRight();
}

////// End of private class //////


DockProperties::DockProperties(QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate(this), parent)
{
}

DockProperties::DockProperties(DockBaseProperties *base,
                               const QVariantMap &settings,
                               QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate(this), parent)
{
    W_D(DockProperties);
    d->copyFromBase(base);
    d->identifier = generateIdentifier();
    d->settings = settings;
}

DockProperties::DockProperties(DockBaseProperties *base,
                               const QString &identifier,
                               const QVariantMap &settings,
                               QObject *parent):
    DockBaseProperties(new DockPropertiesPrivate(this), parent)
{
    W_D(DockProperties);
    d->copyFromBase(base);
    d->identifier = identifier;
    d->settings = settings;
}

DockProperties::DockProperties(DockPropertiesPrivate *dd, QObject *parent):
    DockBaseProperties(dd, parent)
{
}

QString DockProperties::identifier() const
{
    W_D(const DockProperties);
    return d->identifier;
}

QVariantMap DockProperties::settings() const
{
    W_D(const DockProperties);
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
    W_D(DockProperties);
    if (d->settings != settings) {
        d->settings = settings;
        emit settingsChanged(settings);
    }
}

void DockProperties::setIdentifier(const QString &identifier)
{
    W_D(DockProperties);
    if (d->identifier != identifier) {
        d->identifier = identifier;
        emit identifierChanged(identifier);
    }
}


}
