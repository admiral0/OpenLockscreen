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

#include "dockbaseproperties_p.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QVariant>

#include "desktopparser.h"
#include "desktopparserdefines.h"
#include "tools.h"

namespace Widgets
{

static const char *DESKTOP_FILE_SERVICE_VALUE = "dock";
static const char *DESKTOP_FILE_DOCK_INFO_FILE = "X-Widgets-DockInfo-File";

DockBasePropertiesPrivate::DockBasePropertiesPrivate(DockBaseProperties *q):
    GraphicalComponentBasePrivate(q)
{
    anchorsTop = false;
    anchorsBottom = false;
    anchorsLeft = false;
    anchorsRight = false;
    valid = false;
}

DockBasePropertiesPrivate::DockBasePropertiesPrivate(const QString &fileName,
                                                     const QString &packageIdentifier,
                                                     DockBaseProperties *q):
    GraphicalComponentBasePrivate(fileName, packageIdentifier, q)
{
    anchorsTop = false;
    anchorsBottom = false;
    anchorsLeft = false;
    anchorsRight = false;
}

bool DockBasePropertiesPrivate::checkValid(const DesktopParser &parser)
{
    if (parser.value(DESKTOP_FILE_SERVICE_TYPE).toString() != DESKTOP_FILE_SERVICE_VALUE) {
        return false;
    }

    if (!parser.contains(DESKTOP_FILE_DOCK_INFO_FILE)) {
        return false;
    }

    return GraphicalComponentBasePrivate::checkValid(parser);
}

void DockBasePropertiesPrivate::parseDesktopFile(const DesktopParser &parser)
{
    GraphicalComponentBasePrivate::parseDesktopFile(parser);

    QFileInfo fileInfo = QFileInfo(parser.file());
    QDir folder = fileInfo.absoluteDir();

    // Start parsing the QML file for anchors and size
    QString qmlFilePath =
            folder.absoluteFilePath(parser.value(DESKTOP_FILE_DOCK_INFO_FILE).toString());

    QFile qmlFile (qmlFilePath);
    if (!qmlFile.open(QIODevice::ReadOnly)) {
        valid = false;
        return;
    }

    // Cleaned version of the file
    QString data;

    bool haveBlockComment = false;
    QRegExp commentLine ("//(.+)");
    QRegExp blockCommentLineStart ("/\\*.*");
    QRegExp blockCommentLineEnd ("[^*/]*\\*/");
    while (!qmlFile.atEnd()) {
        QString line = qmlFile.readLine();
        line = line.remove(commentLine);

        if (line.indexOf(blockCommentLineStart) != -1) {
            haveBlockComment = true;
            line = line.remove(blockCommentLineStart);
        }

        if (haveBlockComment) {
            int indexOfBlockCommentLineEnd = line.indexOf(blockCommentLineEnd);
            if (indexOfBlockCommentLineEnd != -1) {
                line = line.right(line.size() - indexOfBlockCommentLineEnd);
                line = line.remove(blockCommentLineEnd);

                haveBlockComment = false;
            } else {
                line = "";
            }
        }

        line = line.trimmed();
        if (!line.isEmpty()) {
            line = line.append("\n");
            line = line.replace(";", "\n");
            line = line.replace("{", "\n{\n");
            line = line.replace("}", "\n}\n");
            data.append(line);
        }
    }

    // Prevent anchors brackets to be discarded
    QRegExp anchorsReplaceRegExp ("anchors\\s*\\{([^\\{]*)\\}");
    data.replace(anchorsReplaceRegExp, QString("anchors <\\1>"));

    int firstBracket = data.indexOf("{");
    firstBracket = data.indexOf("{", firstBracket + 1);

    int lastBracket = data.lastIndexOf("}");
    lastBracket = data.lastIndexOf("}", lastBracket - data.size());

    data = data.remove(firstBracket, lastBracket - firstBracket - 1);

    // Check if the document is valid
    bool haveImport = data.contains("import org.SfietKonstantin.widgets");
    bool haveDock = false;
    QRegExp dockRegExp ("Dock(\\s*)\\{");
    if (data.indexOf(dockRegExp) != -1) {
        haveDock = true;
    }

    if (!haveImport || !haveDock) {
        valid = false;
        return;
    }

    // Width and height
    QRegExp widthRegExp ("width\\s*:\\s*(\\d+)");
    QRegExp heightRegExp ("height\\s*:\\s*(\\d+)");

    int width = -1;
    int height = -1;
    if (widthRegExp.indexIn(data) != -1) {
        width = widthRegExp.cap(1).toInt();
    }
    if (heightRegExp.indexIn(data) != -1) {
        height = heightRegExp.cap(1).toInt();
    }
    size.setWidth(width);
    size.setHeight(height);

    // Anchors
    QStringList anchors;
    anchors << "top" << "bottom" << "left" << "right";
    QHash<QString, bool> anchorsOk;
    foreach (QString anchor, anchors) {
        QString anchorsRegExpString = QString("anchors[^>]*%1\\s*:\\s*parent\\s*\\.\\s*%1");
        QRegExp anchorsRegExp (anchorsRegExpString.arg(anchor));
        bool ok = (anchorsRegExp.indexIn(data) != -1);
        anchorsOk.insert(anchor, ok);
    }

    anchorsTop = anchorsOk.value("top");
    anchorsBottom = anchorsOk.value("bottom");
    anchorsLeft = anchorsOk.value("left");
    anchorsRight = anchorsOk.value("right");
    checkAnchorsValid();

    // Has settings
    QRegExp settingsEnabledRegExp ("settingsEnabled\\s*:\\s*(true|false)");
    if (settingsEnabledRegExp.indexIn(data) != -1) {
        QString settingsEnabledString = settingsEnabledRegExp.cap(1);
        settingsEnabled = Tools::stringToBool(settingsEnabledString);
    }


    fileName = parser.value(DESKTOP_FILE_DOCK_INFO_FILE).toString();
}

void DockBasePropertiesPrivate::checkAnchorsValid()
{
    // If width and height are set, must be anchored in a corner
    if (size.width() > 0 && size.height() > 0 &&
        ((anchorsTop && !anchorsBottom && anchorsLeft && !anchorsRight) ||
         (anchorsTop && !anchorsBottom && !anchorsLeft && anchorsRight) ||
         (!anchorsTop && anchorsBottom && anchorsLeft && !anchorsRight) ||
         (!anchorsTop && anchorsBottom && !anchorsLeft && anchorsRight))) {
        return;
    }

    // If only width is set, must be either anchored at left or right side
    if (size.width() > 0 && size.height() <= 0 &&
        ((anchorsTop && anchorsBottom && anchorsLeft && !anchorsRight) ||
         (anchorsTop && anchorsBottom && !anchorsLeft && anchorsRight))) {
        return;
    }

    // If only height is set, must be either anchored at top or bottom side
    if (size.width() <= 0 && size.height() > 0 &&
        ((anchorsTop && !anchorsBottom && anchorsLeft && anchorsRight) ||
         (!anchorsTop && anchorsBottom && anchorsLeft && anchorsRight))) {
        return;
    }

    valid = false;
}

}