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

/**
 * @internal
 * @file abstractsettings_p.h
 * @short Definition of Widgets::AbstractSettingsPrivate
 */

#include "xmlserializableinterface.h"
#include <QtCore/QObject>
#include <QtCore/QMutex>

namespace Widgets
{

static const char *SETTINGS_ELEMENT = "settings";

/**
 * @internal
 * @brief A private class that is used for saving settings to XML
 *
 * This class is used to provide an easy way for components to
 * be saved in XML. It implements Widgets::XmlSerializableInterface
 * and also provide these methods
 * - load()
 * - save()
 * - requestSave()
 *
 * The first and second methods simply use the methods fromXmlElement()
 * and toXmlElement() to load or save the settings. They use the
 * componentName, and QDesktopServices::DataLocation to create the
 * filename and the path of the settings file.
 *
 * It will be in the following form:
 * /path/to/data/location/settings-<componentName>.xml
 *
 * The last method is used to trigger a save request. The save request
 * will be sent to the settingsObject, as a QEvent(QEvent::UpdateEvent).
 * The settingsObject is usually the Q-pointer, and should be able
 * to react to this event and call save().
 *
 * Triggering save requests is a nice way to save settings once when many
 * parameters were modified.
 *
 * In order to use this class, these methods should be implemented:
 * - clear()
 * - fromXmlElement()
 * - toXmlElement()
 *
 * The first method is used to clear settings, and is useful before
 * loading. The second and third method are used to translate the
 * settings into XML.
 */
class AbstractSettingsPrivate: public XmlSerializableInterface
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param settingsObject object that is used to react to the save request.
     */
    AbstractSettingsPrivate(QObject *settingsObject);
    /**
     * @internal
     * @brief Settings file path
     * @return an absolute path to the settings file.
     */
    QString settingsFilePath() const;
    /**
     * @internal
     * @brief Load settings
     */
    void load();
    /**
     * @internal
     * @brief Request a settings save
     */
    void requestSave();
    /**
     * @internal
     * @brief Save settings
     */
    void save();
    /**
     * @internal
     * @brief Clear settings
     *
     * Clear settings. This method is used when
     * load() is called, before loading the settings,
     * in order to clear old settings.
     */
    virtual void clear() = 0;
    /**
     * @internal
     * @brief Load from XML element
     *
     * This method is used to load information from an
     * XML element and translate them into settings.
     *
     * @param element the source XML element.
     * @return if the loading succeded.
     */
    virtual bool fromXmlElement(const QDomElement &element) = 0;
    /**
     * @internal
     * @brief Save to XML element
     *
     * This method is used to save the settings to an XML element.
     *
     * @param tagName the tag that will be used to create this element.
     * @param document a pointer to the document that is used to create elements.
     * @return the class as an XML element.
     */
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const = 0;
    /**
     * @internal
     * @brief Component name
     */
    QString componentName;
private:
    /**
     * @internal
     * @brief object that is used to react to the save request
     */
    QObject *settingsObject;
    /**
     * @internal
     * @brief Mutex that is used to protect load and save
     */
    QMutex mutex;
};

}

#endif // WIDGETS_ABSTRACTSETTINGS_P_H
