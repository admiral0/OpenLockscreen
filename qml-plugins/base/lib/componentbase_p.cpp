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
    q->setDefaultName(parser.value(DESKTOP_FILE_NAME).toString());
    q->setDefaultDescription(parser.value(DESKTOP_FILE_COMMENT).toString());

    QRegExp nameRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_NAME));
    QRegExp commentRegEx (QString("^%1\\[(\\w+)\\]$").arg(DESKTOP_FILE_COMMENT));

    foreach (QString key, keyList) {
        if (nameRegEx.indexIn(key) != -1) {

            QString language = nameRegEx.cap(1);
            q->addName(language, parser.value(DESKTOP_FILE_NAME, language).toString());
        }
        if (commentRegEx.indexIn(key) != -1) {

            QString language = commentRegEx.cap(1);
            q->addDescription(language, parser.value(DESKTOP_FILE_COMMENT, language).toString());
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
