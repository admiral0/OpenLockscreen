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

#include "qmltree_p.h"

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

    QmlTree *tree = QmlTree::fromQml(qmlFile);

    if (!tree) {
        return 0;
    }

    // Import
    bool importOk = false;
    foreach (QString import, tree->imports()) {
        if (import.contains("org.SfietKonstantin.widgets")) {
            importOk = true;
        }
    }

    if (!importOk) {
        delete tree;
        return 0;
    }

    // Name
    if (tree->name() != "Widget") {
        delete tree;
        return 0;
    }

    // Size
    int minimumWidth = -1;
    int minimumHeight = -1;
    if (tree->hasProperty("minimumWidth")) {
        minimumWidth = tree->property("minimumWidth").toInt();
    }
    if (tree->hasProperty("minimumHeight")) {
        minimumHeight = tree->property("minimumHeight").toInt();
    }

    int maximumWidth = -1;
    int maximumHeight = -1;
    if (tree->hasProperty("maximumWidth")) {
        maximumWidth = tree->property("maximumWidth").toInt();
    }
    if (tree->hasProperty("maximumHeight")) {
        maximumHeight = tree->property("maximumHeight").toInt();
    }

    if (minimumWidth == -1 && minimumHeight == -1
        && maximumWidth == -1 && maximumHeight == -1) {
        if (tree->hasProperty("width")) {
            int width = tree->property("width").toInt();
            minimumWidth = width;
            maximumWidth = width;
        }
        if (tree->hasProperty("height")) {
            int height = tree->property("height").toInt();
            minimumHeight = height;
            maximumHeight = height;
        }
    }

    bool sizeOk = (minimumWidth != -1 && minimumHeight != -1 &&
                   maximumWidth != -1 && maximumHeight != -1);
    if (!sizeOk) {
        delete tree;
        return 0;
    }

    delete tree;

    return new WidgetBaseProperties(fileName, disambiguation, settingsFileName,
                                    minimumWidth, minimumHeight, maximumWidth, maximumHeight,
                                    parent);
}

}
