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
 * @file dockbaseproperties.cpp
 * @short Implementation of Widgets::Docks::DockBaseProperties
 */

#include "dockbaseproperties.h"
#include "dockbaseproperties_p.h"

#include <QtCore/QDebug>
#include <QtCore/QFileInfo>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>

#include "tools.h"

namespace Widgets
{

namespace Docks
{

DockBasePropertiesPrivate::DockBasePropertiesPrivate(DockBaseProperties *q):
    GraphicalComponentBasePrivate(q)
{
}

bool DockBasePropertiesPrivate::checkAnchorsValid(bool anchorsTop, bool anchorsBottom,
                                                  bool anchorsLeft, bool anchorsRight,
                                                  const QSize &size)
{
    // If width and height are set, must be anchored in a corner
    if (size.width() > 0 && size.height() > 0 &&
        ((anchorsTop && !anchorsBottom && anchorsLeft && !anchorsRight) ||
         (anchorsTop && !anchorsBottom && !anchorsLeft && anchorsRight) ||
         (!anchorsTop && anchorsBottom && anchorsLeft && !anchorsRight) ||
         (!anchorsTop && anchorsBottom && !anchorsLeft && anchorsRight))) {
        return true;
    }

    // If only width is set, must be either anchored at left or right side
    if (size.width() > 0 && size.height() <= 0 &&
        ((anchorsTop && anchorsBottom && anchorsLeft && !anchorsRight) ||
         (anchorsTop && anchorsBottom && !anchorsLeft && anchorsRight))) {
        return true;
    }

    // If only height is set, must be either anchored at top or bottom side
    if (size.width() <= 0 && size.height() > 0 &&
        ((anchorsTop && !anchorsBottom && anchorsLeft && anchorsRight) ||
         (!anchorsTop && anchorsBottom && anchorsLeft && anchorsRight))) {
        return true;
    }


    return false;
}


////// End of private class //////

DockBaseProperties::DockBaseProperties(QObject *parent):
    GraphicalComponentBase(new DockBasePropertiesPrivate(this), parent)
{
}

DockBaseProperties::DockBaseProperties(const QString &fileName,
                                       const QVariantMap &disambiguation,
                                       const QString &settingsFileName,
                                       int width, int height,
                                       bool anchorsTop, bool anchorsBottom,
                                       bool anchorsLeft, bool anchorsRight,
                                       QObject *parent):
    GraphicalComponentBase(new DockBasePropertiesPrivate(this), parent)
{
    W_D(DockBaseProperties);
    d->fileName = fileName;
    d->disambiguation = disambiguation;
    d->settingsFileName = settingsFileName;
    d->size = QSize(width, height);
    d->anchorsTop = anchorsTop;
    d->anchorsBottom = anchorsBottom;
    d->anchorsLeft = anchorsLeft;
    d->anchorsRight = anchorsRight;
}

DockBaseProperties::DockBaseProperties(DockBasePropertiesPrivate *dd, QObject *parent):
    GraphicalComponentBase(dd, parent)
{
}

int DockBaseProperties::width() const
{
    W_D(const DockBaseProperties);
    return d->size.width();
}

int DockBaseProperties::height() const
{
    W_D(const DockBaseProperties);
    return d->size.height();
}

bool DockBaseProperties::anchorsTop() const
{
    W_D(const DockBaseProperties);
    return d->anchorsTop;
}

bool DockBaseProperties::anchorsBottom() const
{
    W_D(const DockBaseProperties);
    return d->anchorsBottom;
}

bool DockBaseProperties::anchorsLeft() const
{
    W_D(const DockBaseProperties);
    return d->anchorsLeft;
}

bool DockBaseProperties::anchorsRight() const
{
    W_D(const DockBaseProperties);
    return d->anchorsRight;
}

DockBaseProperties * DockBaseProperties::fromQmlFile(const QString &qmlFile,
                                                     const QVariantMap &disambiguation,
                                                     const QString &settingsFileName,
                                                     QObject *parent)
{
    QFileInfo fileInfo (qmlFile);
    if (!fileInfo.exists()) {
        return 0;
    }

    QString fileName = fileInfo.fileName();

    QFile file (qmlFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return 0;
    }

    // Cleaned version of the file
    QString data;

    bool haveBlockComment = false;
    QRegExp commentLine ("//(.+)");
    QRegExp blockCommentLineStart ("/\\*.*");
    QRegExp blockCommentLineEnd ("[^*/]*\\*/");
    while (!file.atEnd()) {
        QString line = file.readLine();
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
    if (!data.contains("import org.SfietKonstantin.widgets.docks")) {
        return 0;
    }

    bool haveDock = false;
    QRegExp dockRegExp ("Dock(\\s*)\\{");
    if (data.indexOf(dockRegExp) != -1) {
        haveDock = true;
    }

    if (!haveDock) {
        return 0;
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
    QSize size (width, height);

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

    bool anchorsTop = anchorsOk.value("top");
    bool anchorsBottom = anchorsOk.value("bottom");
    bool anchorsLeft = anchorsOk.value("left");
    bool anchorsRight = anchorsOk.value("right");

    if (!DockBasePropertiesPrivate::checkAnchorsValid(anchorsTop, anchorsBottom,
                                                      anchorsLeft, anchorsRight,
                                                      size)) {
        return 0;
    }

    return new DockBaseProperties(fileName, disambiguation, settingsFileName,
                                  size.width(), size.height(),
                                  anchorsTop, anchorsBottom, anchorsLeft, anchorsRight,
                                  parent);


}

}

}
