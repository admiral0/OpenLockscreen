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
 * @file componentbase.cpp
 * @short Implementation of Widgets::ComponentBase
 */

#include "componentbase.h"
#include "componentbase_p.h"

#include <QtCore/QDebug>
#include <QtCore/QLocale>
#include <QtCore/QVariant>

#include "qplatformdefs.h"
#ifdef MEEGO_EDITION_HARMATTAN
#include <MLocale>
#endif

#include "desktopparser.h"
#include "desktopparserdefines.h"

namespace Widgets
{

/**
 * @internal
 * @brief DESKTOP_FILE_NAME
 */
static const char *DESKTOP_FILE_NAME = "Name";
/**
 * @internal
 * @brief DESKTOP_FILE_COMMENT
 */
static const char *DESKTOP_FILE_COMMENT = "Comment";
/**
 * @internal
 * @brief DESKTOP_FILE_ICON
 */
static const char *DESKTOP_FILE_ICON = "Icon";
/**
 * @internal
 * @brief DESKTOP_FILE_TYPE
 */
static const char *DESKTOP_FILE_TYPE = "Type";
/**
 * @internal
 * @brief DESKTOP_FILE_TYPE_VALUE
 */
static const char *DESKTOP_FILE_TYPE_VALUE = "Service";



ComponentBasePrivate::ComponentBasePrivate(ComponentBase *q):
    q_ptr(q)
{
    valid = false;
}

ComponentBasePrivate::~ComponentBasePrivate()
{
}

void ComponentBasePrivate::fromDesktopFile(const QString &file)
{
    DesktopParser parser (file);
    parser.beginGroup("Desktop Entry");

    parseDesktopFile(parser);

    parser.endGroup();
}

void ComponentBasePrivate::parseDesktopFile(const DesktopParser &parser)
{
    Q_Q(ComponentBase);
    valid = checkValid(parser);
    if (!valid) {
        return;
    }

    QStringList keyList = parser.keys();

    // Fetch icon
    q->setIcon(parser.value(DESKTOP_FILE_ICON).toString());

    // Fetch names and comments
    QVariant nameVariant = parser.value(DESKTOP_FILE_NAME);
    if (nameVariant.type() == QVariant::String) {
        q->setDefaultName(nameVariant.toString());
    } else if (nameVariant.type() == QVariant::StringList) {
        QString name = nameVariant.toStringList().join(", ");
        q->setDefaultName(name);
    } else {
        q->setDefaultName("");
    }
    QVariant descriptionVariant = parser.value(DESKTOP_FILE_COMMENT);
    if (descriptionVariant.type() == QVariant::String) {
        q->setDefaultDescription(descriptionVariant.toString());
    } else if (descriptionVariant.type() == QVariant::StringList) {
        QString name = descriptionVariant.toStringList().join(", ");
        q->setDefaultDescription(name);
    } else {
        q->setDefaultDescription("");
    }

    QRegExp nameRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_NAME));
    QRegExp commentRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_COMMENT));

    foreach (QString key, keyList) {
        if (nameRegEx.indexIn(key) != -1) {

            QString language = nameRegEx.cap(1);
            nameVariant = parser.value(DESKTOP_FILE_NAME, language);
            if (nameVariant.type() == QVariant::String) {
                q->addName(language, nameVariant.toString());
            } else if (nameVariant.type() == QVariant::StringList) {
                QString name = nameVariant.toStringList().join(", ");
                q->addName(language, name);
            } else {
                q->addName(language, "");
            }
        }
        if (commentRegEx.indexIn(key) != -1) {

            QString language = commentRegEx.cap(1);
            descriptionVariant = parser.value(DESKTOP_FILE_COMMENT, language);
            if (descriptionVariant.type() == QVariant::String) {
                q->addDescription(language, descriptionVariant.toString());
            } else if (descriptionVariant.type() == QVariant::StringList) {
                QString name = descriptionVariant.toStringList().join(", ");
                q->addDescription(language, name);
            } else {
                q->addDescription(language, "");
            }
        }
    }

}

bool ComponentBasePrivate::checkValid(const DesktopParser &parser)
{
    if (!parser.contains(DESKTOP_FILE_NAME)) {
        return false;
    }
    if (!parser.contains(DESKTOP_FILE_COMMENT)) {
        return false;
    }
    if (parser.value(DESKTOP_FILE_TYPE).toString() != DESKTOP_FILE_TYPE_VALUE) {
        return false;
    }
    if (!parser.contains(DESKTOP_FILE_SERVICE_TYPE)) {
        return false;
    }
    return true;
}

////// End of private class //////

ComponentBase::ComponentBase(QObject *parent):
    QObject(parent), d_pointer(new ComponentBasePrivate(this))
{
}

ComponentBase::ComponentBase(ComponentBasePrivate *dd, QObject *parent):
    QObject(parent), d_pointer(dd)
{
}

ComponentBase::~ComponentBase()
{
}

bool ComponentBase::isValid() const
{
    W_D(const ComponentBase);
    return d->valid;
}

QString ComponentBase::icon() const
{
    W_D(const ComponentBase);
    return d->icon;
}

QStringList ComponentBase::languages() const
{
    W_D(const ComponentBase);
    return d->nameAndDescription.keys();
}

QString ComponentBase::defaultName() const
{
    W_D(const ComponentBase);
    return d->defaultName;
}

QString ComponentBase::name() const
{
    W_D(const ComponentBase);

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
            value = d->nameAndDescription.value(trueLanguage).first;
        }
    }

    if (value.isEmpty()) {
        value = d->defaultName;
    }
    return value;
}

QString ComponentBase::name(const QString &language) const
{
    W_D(const ComponentBase);

    QString value = d->nameAndDescription.value(language).first;
    if (value.isEmpty()) {
        value = d->defaultName;
    }

    return value;
}

QString ComponentBase::defaultDescription() const
{
    W_D(const ComponentBase);
    return d->defaultDescription;
}

QString ComponentBase::description() const
{
    W_D(const ComponentBase);
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
            value = d->nameAndDescription.value(trueLanguage).second;
        }
    }

    if (value.isEmpty()) {
        value = d->defaultDescription;
    }
    return value;
}

QString ComponentBase::description(const QString &language) const
{
    W_D(const ComponentBase);
    QString value = d->nameAndDescription.value(language).second;
    if (value.isEmpty()) {
        value = d->defaultDescription;
    }

    return value;
}

void ComponentBase::setIcon(const QString &icon)
{
    W_D(ComponentBase);
    if (d->icon != icon) {
        d->icon = icon;
        emit iconChanged();
    }
}

void ComponentBase::setDefaultName(const QString &name)
{
    W_D(ComponentBase);
    if (d->defaultName != name) {
        d->defaultName = name;
        emit defaultNameChanged();
    }
}

void ComponentBase::addName(const QString &language, const QString &name)
{
    W_D(ComponentBase);
    QPair<QString, QString> data;

    if (d->nameAndDescription.contains(language)) {
        data = d->nameAndDescription.value(language);
    }

    data.first = name;
    d->nameAndDescription.insert(language, data);
    emit nameChanged();
}

void ComponentBase::setDefaultDescription(const QString &description)
{
    W_D(ComponentBase);

    if (d->defaultDescription != description) {
        d->defaultDescription = description;
        emit descriptionChanged();
    }
}

void ComponentBase::addDescription(const QString &language, const QString &description)
{
    W_D(ComponentBase);
    QPair<QString, QString> data;

    if (d->nameAndDescription.contains(language)) {
        data = d->nameAndDescription.value(language);
    }
    data.second = description;
    d->nameAndDescription.insert(language, data);
    emit descriptionChanged();
}

void ComponentBase::clearNamesAndDescriptions()
{
    W_D(ComponentBase);
    d->nameAndDescription.clear();
    emit nameChanged();
    emit descriptionChanged();
}

}
