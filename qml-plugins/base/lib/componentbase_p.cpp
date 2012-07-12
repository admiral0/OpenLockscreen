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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include "componentbase_p.h"

#include <QtCore/QDebug>
#include <QtCore/QVariant>

#include "desktopparser.h"
#include "desktopparserdefines.h"

namespace Widgets
{

static const char *DESKTOP_FILE_NAME = "Name";
static const char *DESKTOP_FILE_COMMENT = "Comment";
static const char *DESKTOP_FILE_ICON = "Icon";
static const char *DESKTOP_FILE_TYPE = "Type";
static const char *DESKTOP_FILE_TYPE_VALUE = "Service";

ComponentBasePrivate::ComponentBasePrivate(ComponentBase *q):
    q_ptr(q)
{
    valid = false;
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

}
