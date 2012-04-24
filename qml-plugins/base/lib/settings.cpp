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

#include "settings.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtCore/QVariantMap>
#include <QtGui/QDesktopServices>

#include "abstractsettings_p.h"
#include "widgets_global.h"
#include "xmlserializableinterface.h"


namespace Widgets
{

static const char *GROUP_ELEMENT = "group";
static const char *GROUP_ATTRIBUTE = "group";
static const char *PAIR_ELEMENT = "pair";
static const char *KEY_ATTRIBUTE = "key";
static const char *VALUE_ATTRIBUTE = "value";

class SettingsPrivate: public AbstractSettingsPrivate
{
public:
    SettingsPrivate(Settings *q = 0);
    void setDefaultValue(const QString &group, const QString &key, const QVariant &value);
    void copyDefaultValues();
    virtual void clear();
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    QMap<QString, QVariantMap> defaultSettings;
    QMap<QString, QVariantMap> settings;
    QString currentGroup;

private:
    Q_DECLARE_PUBLIC(Settings)
    Settings * const q_ptr;
};

SettingsPrivate::SettingsPrivate(Settings *q):
    AbstractSettingsPrivate(q), q_ptr(q)
{
}

void SettingsPrivate::setDefaultValue(const QString &group, const QString &key,
                                      const QVariant &value)
{
    Q_Q(Settings);

    if (!defaultSettings.contains(group)) {
        defaultSettings.insert(group, QVariantMap());
    }

    if(!defaultSettings[group].contains(key)) {
        defaultSettings[group].insert(key, value);
        emit q->valueChanged(group, key, value);
    }

    if (!settings.contains(group)) {
        settings.insert(group, QVariantMap());
    }

    if(!settings[group].contains(key)) {
        settings[group].insert(key, value);
        emit q->valueChanged(group, key, value);
        requestSave();
    }
}

void SettingsPrivate::copyDefaultValues()
{
    QMapIterator<QString, QVariantMap> groupIterator =
            QMapIterator<QString, QVariantMap>(defaultSettings);
    while (groupIterator.hasNext()) {
        groupIterator.next();
        QString group = groupIterator.key();
        QVariantMap pair = groupIterator.value();

        if (!settings.contains(group)) {
            settings.insert(group, QVariantMap());
        }

        QMapIterator<QString, QVariant> pairIterator =
                QMapIterator<QString, QVariant>(pair);
        while (pairIterator.hasNext()) {
            pairIterator.next();
            QString key = pairIterator.key();
            QVariant value = pairIterator.value();

            if (!settings[group].contains(key)) {
                settings[group].insert(key, value);
            }
        }
    }
}

void SettingsPrivate::clear()
{
    settings.clear();
}

bool SettingsPrivate::fromXmlElement(const QDomElement &element)
{
    if (element.tagName() != SETTINGS_ELEMENT) {
        return false;
    }

    QDomElement groupElement = element.firstChildElement(GROUP_ELEMENT);
    while (!groupElement.isNull()) {
        QString group = groupElement.attribute(GROUP_ATTRIBUTE);
        if (!settings.contains(group)) {
            settings.insert(group, QVariantMap());
        }

        QDomElement pairElement = groupElement.firstChildElement(PAIR_ELEMENT);
        while (!pairElement.isNull()) {
            QString key = pairElement.attribute(KEY_ATTRIBUTE);
            QVariant value = QVariant(pairElement.attribute(VALUE_ATTRIBUTE));

            settings[group].insert(key, value);

            pairElement = pairElement.nextSiblingElement(PAIR_ELEMENT);
        }
        groupElement = groupElement.nextSiblingElement(GROUP_ELEMENT);
    }

    return true;
}

QDomElement SettingsPrivate::toXmlElement(const QString &tagName, QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);

    QMapIterator<QString, QVariantMap> groupIterator =
            QMapIterator<QString, QVariantMap>(settings);
    while (groupIterator.hasNext()) {
        groupIterator.next();
        QString group = groupIterator.key();
        QVariantMap pair = groupIterator.value();

        QDomElement groupElement = document->createElement(GROUP_ELEMENT);
        groupElement.setAttribute(GROUP_ATTRIBUTE, group);

        QMapIterator<QString, QVariant> pairIterator =
                QMapIterator<QString, QVariant>(pair);

        while (pairIterator.hasNext()) {
            pairIterator.next();
            QString key = pairIterator.key();
            QVariant value = pairIterator.value();

            QDomElement pairElement = document->createElement(PAIR_ELEMENT);
            pairElement.setAttribute(KEY_ATTRIBUTE, key);
            pairElement.setAttribute(VALUE_ATTRIBUTE, value.toString());

            groupElement.appendChild(pairElement);
        }

        element.appendChild(groupElement);
    }

    return element;
}

////// End of private class //////

Settings::Settings(QObject *parent):
    QObject(parent), d_ptr(new SettingsPrivate(this))
{
}

Settings::Settings(SettingsPrivate *dd, QObject *parent):
    QObject(parent), d_ptr(dd)
{
}

Settings::~Settings()
{
}

void Settings::setGroup(const QString &group)
{
    Q_D(Settings);
    d->currentGroup = group;
}

void Settings::clearGroup()
{
    Q_D(Settings);
    d->currentGroup = QString();
}

QVariant Settings::value(const QString &key) const
{
    Q_D(const Settings);
    return value(d->currentGroup, key);
}

QVariant Settings::value(const QString &group, const QString &key) const
{

    Q_D(const Settings);
    return d->settings.value(group).value(key);
}

QDeclarativeListProperty<SettingsEntry> Settings::defaultSettings()
{
    return QDeclarativeListProperty<SettingsEntry>(this, 0,
                                                   &Widgets::Settings::appendDefaultSettings);
}

void Settings::reload()
{
    Q_D(Settings);

    d->load();
    d->copyDefaultValues();
}

void Settings::setComponentName(const QString &componentName)
{
    Q_D(Settings);
    if (d->componentName != componentName) {
        d->componentName = componentName;
        emit componentNameChanged(componentName);

        reload();
    }
}

void Settings::setValue(const QString &key, const QVariant &value)
{
    Q_D(Settings);
    setValue(d->currentGroup, key, value);
}

void Settings::setValue(const QString &group, const QString &key, const QVariant &value)
{
    Q_D(Settings);
    if (!d->settings.contains(group)) {
        d->settings.insert(group, QVariantMap());
    }

    if(d->settings[group].value(key) != value) {
        d->settings[group].insert(key, value);
        emit valueChanged(group, key, value);
        d->requestSave();
    }
}

bool Settings::event(QEvent *event)
{
    Q_D(Settings);
    if (event->type() == QEvent::UpdateRequest) {
        d->save();
        return true;
    }
    return QObject::event(event);
}

void Settings::appendDefaultSettings(QDeclarativeListProperty<SettingsEntry> *list,
                                     SettingsEntry *entry)
{
    Settings *settings = qobject_cast<Settings *>(list->object);
    if(settings) {
        settings->d_func()->setDefaultValue(entry->group(), entry->key(), entry->value());
    }
}

}

#include "moc_settings.cpp"
