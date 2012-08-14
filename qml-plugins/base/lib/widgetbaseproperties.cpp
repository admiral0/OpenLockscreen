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
 * @file widgetbaseproperties.cpp
 * @short Implementation of Widgets::WidgetBaseProperties
 */

#include "widgetbaseproperties.h"
#include "widgetbaseproperties_p.h"

#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QRegExp>

namespace Widgets
{

WidgetBasePropertiesPrivate::WidgetBasePropertiesPrivate(WidgetBaseProperties *q):
    GraphicalComponentBasePrivate(q)
{
}

////// End of private class //////

WidgetBaseProperties::WidgetBaseProperties(QObject *parent):
    GraphicalComponentBase(new WidgetBasePropertiesPrivate(this), parent)
{
}

WidgetBaseProperties::WidgetBaseProperties(const QString &fileName,
                                           const QVariantMap &disambiguation,
                                           const QString &settingsFileName,
                                           int minimumWidth, int minimumHeight,
                                           int maximumWidth, int maximumHeight,
                                           QObject *parent):
    GraphicalComponentBase(new WidgetBasePropertiesPrivate(this), parent)
{
    W_D(WidgetBaseProperties);
    d->fileName = fileName;
    d->disambiguation = disambiguation;
    d->settingsFileName = settingsFileName;
    d->minimumSize = QSize(minimumWidth, minimumHeight);
    d->maximumSize = QSize(maximumWidth, maximumHeight);
}

WidgetBaseProperties::WidgetBaseProperties(WidgetBasePropertiesPrivate *dd, QObject *parent):
    GraphicalComponentBase(dd, parent)
{
}

int WidgetBaseProperties::minimumWidth() const
{
    W_D(const WidgetBaseProperties);
    return d->minimumSize.width();
}

int WidgetBaseProperties::minimumHeight() const
{
    W_D(const WidgetBaseProperties);
    return d->minimumSize.height();
}

int WidgetBaseProperties::maximumWidth() const
{
    W_D(const WidgetBaseProperties);
    return d->maximumSize.width();
}

int WidgetBaseProperties::maximumHeight() const
{
    W_D(const WidgetBaseProperties);
    return d->maximumSize.height();
}

WidgetBaseProperties * WidgetBaseProperties::fromQmlFile(const QString &qmlFile,
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

    int firstBracket = data.indexOf("{");
    firstBracket = data.indexOf("{", firstBracket + 1);

    int lastBracket = data.lastIndexOf("}");
    lastBracket = data.lastIndexOf("}", lastBracket - data.size());

    data = data.remove(firstBracket, lastBracket - firstBracket - 1);

    // Check if the document is valid
    if(!data.contains("import org.SfietKonstantin.widgets")) {
        return 0;
    }

    bool haveWidget = false;
    QRegExp dockRegExp ("Widget(\\s*)\\{");
    if (data.indexOf(dockRegExp) != -1) {
        haveWidget = true;
    }

    if (!haveWidget) {
        return 0;
    }

    // Width and height
    QRegExp minimumWidthRegExp ("minimumWidth\\s*:\\s*(\\d+)");
    QRegExp minimumHeightRegExp ("minimumHeight\\s*:\\s*(\\d+)");

    int minimumWidth = -1;
    int minimumHeight = -1;
    if (minimumWidthRegExp.indexIn(data) != -1) {
        minimumWidth = minimumWidthRegExp.cap(1).toInt();
    }
    if (minimumHeightRegExp.indexIn(data) != -1) {
        minimumHeight = minimumHeightRegExp.cap(1).toInt();
    }

    QRegExp maximumWidthRegExp ("maximumWidth\\s*:\\s*(\\d+)");
    QRegExp maximumHeightRegExp ("maximumHeight\\s*:\\s*(\\d+)");

    int maximumWidth = -1;
    int maximumHeight = -1;
    if (maximumWidthRegExp.indexIn(data) != -1) {
        maximumWidth = maximumWidthRegExp.cap(1).toInt();
    }
    if (maximumHeightRegExp.indexIn(data) != -1) {
        maximumHeight = maximumHeightRegExp.cap(1).toInt();
    }

    QRegExp widthRegExp ("width\\s*:\\s*(\\d+)");
    QRegExp heightRegExp ("height\\s*:\\s*(\\d+)");

    if (minimumWidth == -1 && minimumHeight == -1
        && maximumWidth == -1 && maximumHeight == -1) {
        if (widthRegExp.indexIn(data) != -1) {
            int width = widthRegExp.cap(1).toInt();
            minimumWidth = width;
            maximumWidth = width;
        }
        if (heightRegExp.indexIn(data) != -1) {
            int height = heightRegExp.cap(1).toInt();
            minimumHeight = height;
            maximumHeight = height;
        }
    }

    bool sizeOk = (minimumWidth != -1 && minimumHeight != -1 &&
                   maximumWidth != -1 && maximumHeight != -1);
    if (!sizeOk) {
        return 0;
    }

    return new WidgetBaseProperties(fileName, disambiguation, settingsFileName,
                                    minimumWidth, minimumHeight, maximumWidth, maximumHeight,
                                    parent);
}

}
