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

#include "abstractsettings_p.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QMutexLocker>
#include <QtGui/QDesktopServices>

#include "widgets_global.h"

namespace Widgets
{

AbstractSettingsPrivate::AbstractSettingsPrivate(QObject *settingsObject):
    XmlSerializableInterface(), settingsObject(settingsObject), mutex()
{
}

QString AbstractSettingsPrivate::settingsFilePath() const
{
    QString settingsFileName = QString("settings-%1.xml").arg(componentName);

    QDir dir (QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    QDir::root().mkpath(dir.absolutePath());

    return dir.absoluteFilePath(settingsFileName);
}

void AbstractSettingsPrivate::load()
{
    QMutexLocker locker (&mutex);
    Q_UNUSED(locker)
    if (componentName.isEmpty()) {
        return;
    }

    clear();

    QFile *input = new QFile(settingsFilePath());
    if (!input->exists()) {
        return;
    }
    W_ASSERT(input->open(QIODevice::ReadOnly));

    QDomDocument document = QDomDocument();
    if (document.setContent(input)) {
        W_ASSERT(fromXmlElement(document.documentElement()));
    }

    input->close();
    input->deleteLater();
}

void AbstractSettingsPrivate::requestSave()
{
    QCoreApplication::postEvent(settingsObject, new QEvent(QEvent::UpdateRequest));
}

void AbstractSettingsPrivate::save()
{
    if (componentName.isEmpty()) {
        return;
    }

    QFile *output = new QFile(settingsFilePath());
    W_ASSERT(output->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate));

    QDomDocument outputDocument = QDomDocument();

    // Declaration
    QDomProcessingInstruction xmlDeclaration =
                outputDocument.createProcessingInstruction("xml", "version=\"1.0\"");
        outputDocument.appendChild(xmlDeclaration);
    QDomElement element = toXmlElement(SETTINGS_ELEMENT, &outputDocument);
    outputDocument.appendChild(element);

    output->write(outputDocument.toByteArray(2));

    output->close();
    output->deleteLater();
}

}
