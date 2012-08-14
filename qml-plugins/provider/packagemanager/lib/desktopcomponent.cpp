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
 * @file desktopcomponent.cpp
 * @short Implementation of Widgets::Provider::PackageManager::DesktopComponent
 */

#include "desktopcomponent.h"
#include "desktopcomponent_p.h"

#include <QtCore/QDebug>
#include <QtCore/QLocale>
#include <QtCore/QVariant>

#include "qplatformdefs.h"
#ifdef MEEGO_EDITION_HARMATTAN
#include <MLocale>
#endif

#include "desktopfileparser_p.h"
#include "desktopfileparserdefines_p.h"

namespace Widgets
{

namespace Provider
{

namespace PackageManager
{

/**
 * @internal
 * @brief DESKTOP_FILE_NAME
 *
 * Used in Widgets::Provider::PackageManager::DesktopComponent.
 */
static const char *DESKTOP_FILE_NAME = "Name";
/**
 * @internal
 * @brief DESKTOP_FILE_COMMENT
 *
 * Used in Widgets::Provider::PackageManager::DesktopComponent.
 */
static const char *DESKTOP_FILE_COMMENT = "Comment";
/**
 * @internal
 * @brief DESKTOP_FILE_ICON
 *
 * Used in Widgets::Provider::PackageManager::DesktopComponent.
 */
static const char *DESKTOP_FILE_ICON = "Icon";
/**
 * @internal
 * @brief DESKTOP_FILE_TYPE
 *
 * Used in Widgets::Provider::PackageManager::DesktopComponent.
 */
static const char *DESKTOP_FILE_TYPE = "Type";
/**
 * @internal
 * @brief DESKTOP_FILE_TYPE_VALUE
 *
 * Used in Widgets::Provider::PackageManager::DesktopComponent.
 */
static const char *DESKTOP_FILE_TYPE_VALUE = "Service";



DesktopComponentPrivate::DesktopComponentPrivate(DesktopComponent *q):
    q_ptr(q)
{
}

DesktopComponentPrivate::~DesktopComponentPrivate()
{
}

DesktopComponentBuilderHelper::DesktopComponentBuilderHelper():
    m_parent(0)
{
}

DesktopComponentBuilderHelper::~DesktopComponentBuilderHelper()
{
    delete desktopFileParser;
}

void DesktopComponentBuilderHelper
            ::setProperties(const QString &desktopFile, QObject *parent)
{
    desktopFileParser = new DesktopFileParser(desktopFile);
    desktopFileParser->beginGroup("Desktop Entry");
    m_parent = parent;
}

QObject * DesktopComponentBuilderHelper::parent() const
{
    return m_parent;
}

bool DesktopComponentBuilderHelper::isValid() const
{
    if (!desktopFileParser->contains(DESKTOP_FILE_NAME)) {
        return false;
    }
    if (!desktopFileParser->contains(DESKTOP_FILE_COMMENT)) {
        return false;
    }
    if (desktopFileParser->value(DESKTOP_FILE_TYPE).toString() != DESKTOP_FILE_TYPE_VALUE) {
        return false;
    }
    if (!desktopFileParser->contains(SERVICE_TYPE)) {
        return false;
    }
    return true;
}

QString DesktopComponentBuilderHelper::defaultName() const
{
    QVariant nameVariant = desktopFileParser->value(DESKTOP_FILE_NAME);
    if (nameVariant.type() == QVariant::String) {
        return nameVariant.toString();
    } else {
        return QString();
    }
}

QString DesktopComponentBuilderHelper::defaultDescription() const
{
    QVariant descriptionVariant = desktopFileParser->value(DESKTOP_FILE_COMMENT);
    if (descriptionVariant.type() == QVariant::String) {
        return descriptionVariant.toString();
    } else {
        return QString();
    }
}

QHash<QString, QString> DesktopComponentBuilderHelper::names() const
{
    QRegExp nameRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_NAME));

    QHash<QString, QString> data;

    foreach (QString key, desktopFileParser->keys()) {
        if (nameRegEx.indexIn(key) != -1) {
            QString language = nameRegEx.cap(1);
            QVariant nameVariant = desktopFileParser->value(DESKTOP_FILE_NAME, language);
            if (nameVariant.type() == QVariant::String) {
                data.insert(language, nameVariant.toString());
            }
        }
    }

    return data;
}

QHash<QString, QString> DesktopComponentBuilderHelper::descriptions() const
{
    QRegExp commentRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_COMMENT));

    QHash<QString, QString> data;

    foreach (QString key, desktopFileParser->keys()) {
        if (commentRegEx.indexIn(key) != -1) {
            QString language = commentRegEx.cap(1);
            QVariant commentVariant = desktopFileParser->value(DESKTOP_FILE_NAME, language);
            if (commentVariant.type() == QVariant::String) {
                data.insert(language, commentVariant.toString());
            }
        }
    }
    return data;
}

QString DesktopComponentBuilderHelper::icon() const
{
    return desktopFileParser->value(DESKTOP_FILE_ICON).toString();
}

DesktopComponentBuilder::DesktopComponentBuilder():
    AbstractBuilder<DesktopComponent *>()
{
    m_helper = new DesktopComponentBuilderHelper();
}

DesktopComponentBuilder::~DesktopComponentBuilder()
{
    delete m_helper;
}

void DesktopComponentBuilder::setProperties(const QString &desktopFile, QObject *parent)
{
    m_helper->setProperties(desktopFile, parent);
}

void DesktopComponentBuilder::buildElement()
{
    if (!m_helper->isValid()) {
        builtElement = 0;
        return;
    }
    builtElement = new DesktopComponent(m_helper->icon(),
                                        m_helper->defaultName(), m_helper->defaultDescription(),
                                        m_helper->names(), m_helper->descriptions(),
                                        m_helper->parent());
}

////// End of private class //////

DesktopComponent::DesktopComponent(const QString &icon,
                                   const QString &defaultName, const QString &defaultDescription,
                                   const QHash<QString, QString> &names,
                                   const QHash<QString, QString> &descriptions,
                                   QObject *parent):
    QObject(parent), d_pointer(new DesktopComponentPrivate(this))
{
    W_D(DesktopComponent);
    d->icon = icon;
    d->defaultName = defaultName;
    d->defaultDescription = defaultDescription;
    d->names = names;
    d->descriptions = descriptions;
}

DesktopComponent::DesktopComponent(DesktopComponentPrivate *dd, QObject *parent):
    QObject(parent), d_pointer(dd)
{
}

DesktopComponent::~DesktopComponent()
{
}

QString DesktopComponent::icon() const
{
    W_D(const DesktopComponent);
    return d->icon;
}

QStringList DesktopComponent::languages() const
{
    W_D(const DesktopComponent);

    QStringList languages = d->names.keys();
    foreach (QString language, d->descriptions.keys()) {
        if (!languages.contains(language)) {
            languages.append(language);
        }
    }

    return languages;
}

QString DesktopComponent::defaultName() const
{
    W_D(const DesktopComponent);
    return d->defaultName;
}

QString DesktopComponent::name() const
{
    W_D(const DesktopComponent);

#if (QT_VERSION < QT_VERSION_CHECK(4, 8, 0))
#  ifndef MEEGO_EDITION_HARMATTAN
    QStringList languages;
#  else
    MLocale locale = MLocale();
    QStringList languages;
    languages.append(locale.name());
    languages.append(locale.language());
    languages.append(QString("%1_%2").arg(locale.language()).arg(locale.country()));
#  endif
#else
    QStringList languages = QLocale::system().uiLanguages();
#endif
    QListIterator<QString> languagesIterator = QListIterator<QString>(languages);

    QString value = QString();
    QRegExp languageRegExp = QRegExp("(\\w+)(\\..+){0,1}");

    while (languagesIterator.hasNext() && value.isEmpty()) {
        QString language = languagesIterator.next();
        if (language.indexOf(languageRegExp) != -1) {
            QString trueLanguage = languageRegExp.cap(1);
            value = d->names.value(trueLanguage);
        }
    }

    if (value.isEmpty()) {
        value = d->defaultName;
    }
    return value;
}

QString DesktopComponent::name(const QString &language) const
{
    W_D(const DesktopComponent);

    QString value = d->names.value(language);
    if (value.isEmpty()) {
        value = d->defaultName;
    }

    return value;
}

QString DesktopComponent::defaultDescription() const
{
    W_D(const DesktopComponent);
    return d->defaultDescription;
}

QString DesktopComponent::description() const
{
    W_D(const DesktopComponent);
#if (QT_VERSION < QT_VERSION_CHECK(4, 8, 0))
#  ifndef MEEGO_EDITION_HARMATTAN
    QStringList languages;
#  else
    MLocale locale = MLocale();
    QStringList languages;
    languages.append(locale.name());
    languages.append(locale.language());
    languages.append(QString("%1_%2").arg(locale.language()).arg(locale.country()));
#  endif
#else
    QStringList languages = QLocale::system().uiLanguages();
#endif
    QListIterator<QString> languagesIterator = QListIterator<QString>(languages);

    QString value = QString();
    QRegExp languageRegExp = QRegExp("(\\w+)(\\..+){0,1}");

    while (languagesIterator.hasNext() && value.isEmpty()) {
        QString language = languagesIterator.next();
        if (language.indexOf(languageRegExp) != -1) {
            QString trueLanguage = languageRegExp.cap(1);
            value = d->descriptions.value(trueLanguage);
        }
    }

    if (value.isEmpty()) {
        value = d->defaultDescription;
    }
    return value;
}

QString DesktopComponent::description(const QString &language) const
{
    W_D(const DesktopComponent);
    QString value = d->descriptions.value(language);
    if (value.isEmpty()) {
        value = d->defaultDescription;
    }

    return value;
}

}

}

}
