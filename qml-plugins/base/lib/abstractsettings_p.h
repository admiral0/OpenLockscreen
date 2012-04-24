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

#ifndef WIDGETS_ABSTRACTSETTINGS_P_H
#define WIDGETS_ABSTRACTSETTINGS_P_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

#include "xmlserializableinterface.h"
#include <QtCore/QObject>

namespace Widgets
{

static const char *SETTINGS_ELEMENT = "settings";

class AbstractSettingsPrivate: public XmlSerializableInterface
{
public:
    AbstractSettingsPrivate(QObject *settingsObject);
    QString settingsFilePath() const;
    void load();
    void requestSave();
    void save();
    virtual void clear() = 0;
    virtual bool fromXmlElement(const QDomElement &element) = 0;
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const = 0;
    QString componentName;
private:
    QObject *settingsObject;
};

}

#endif // WIDGETS_ABSTRACTSETTINGS_P_H