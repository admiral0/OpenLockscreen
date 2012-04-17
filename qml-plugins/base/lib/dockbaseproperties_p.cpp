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

#include "dockbaseproperties_p.h"
#include "desktopparserdefines.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QVariant>

#include "desktopparser.h"
#include "tools.h"

namespace Widgets
{

static const char *DESKTOP_FILE_SERVICE_VALUE = "dock";
static const char *DESKTOP_FILE_DOCK_INFO_FILE = "X-Widgets-DockInfo-File";

DockBasePropertiesPrivate::DockBasePropertiesPrivate():
    GraphicalElementBasePropertiesPrivate()
{
    anchorsTop = false;
    anchorsBottom = false;
    anchorsLeft = false;
    anchorsRight = false;
    valid = false;
}

void DockBasePropertiesPrivate::checkValid()
{
    // Width and height and no anchors are set
    if (size.width() > 0 && size.height() > 0 &&
        !anchorsTop && !anchorsBottom && !anchorsLeft && !anchorsRight) {
        valid = true;
        return;
    }

    // Width is set and either top or bottom anchored
    if (size.width() > 0 && size.height() <= 0 &&
        ((anchorsTop && !anchorsBottom) || (!anchorsTop && anchorsBottom)) &&
        !anchorsLeft && !anchorsRight) {
        valid = true;
        return;
    }

    // Height is set and either left or right anchored
    if (size.height() > 0 && size.width() <= 0 &&
        ((anchorsLeft && !anchorsRight) || (!anchorsRight && anchorsLeft)) &&
        !anchorsTop && !anchorsBottom) {
        valid = true;
        return;
    }
}

void DockBasePropertiesPrivate::fromDesktopFile(const QString &file,
                                                const QString &packageIdentifier)
{
    DesktopParser parser (file);
    parser.beginGroup("Desktop Entry");

    if (!parser.contains(DESKTOP_FILE_NAME)) {
        return;
    }
    if (!parser.contains(DESKTOP_FILE_COMMENT)) {
        return;
    }
    if (parser.value(DESKTOP_FILE_TYPE).toString() != DESKTOP_FILE_TYPE_VALUE) {
        return;
    }
    if (parser.value(DESKTOP_FILE_SERVICE_TYPE).toString() != DESKTOP_FILE_SERVICE_VALUE) {
        return;
    }
    if (parser.value(DESKTOP_FILE_DOCK_INFO_FILE).toString().isEmpty()) {
        return;
    }

    QFileInfo fileInfo = QFileInfo(parser.file());
    QDir folder = fileInfo.absoluteDir();

    // Start parsing the QML file for anchors and size
    QString qmlFilePath =
            folder.absoluteFilePath(parser.value(DESKTOP_FILE_DOCK_INFO_FILE).toString());

    QFile qmlFile (qmlFilePath);
    if (!qmlFile.open(QIODevice::ReadOnly)) {
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
    checkValid();

    // Has settings
    QRegExp settingsEnabledRegExp ("settingsEnabled\\s*:\\s*(true|false)");
    if (settingsEnabledRegExp.indexIn(data) != -1) {
        QString settingsEnabledString = settingsEnabledRegExp.cap(1);
        settingsEnabled = Tools::stringToBool(settingsEnabledString);
    }



    fileName = parser.value(DESKTOP_FILE_DOCK_INFO_FILE).toString();
    this->packageIdentifier = packageIdentifier;

    parser.endGroup();

    return;
}

}
