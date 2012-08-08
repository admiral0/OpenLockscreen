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

#ifndef WIDGETS_GRAPHICALCOMPONENTBASE_H
#define WIDGETS_GRAPHICALCOMPONENTBASE_H

/**
 * @file graphicalcomponentbase.h
 * @short Definition of Widgets::GraphicalComponentBase
 */

#include <QtCore/QObject>
#include <QtCore/QVariantHash>

#include "widgets_global.h"

#include "xmlserializableinterface.h"

namespace Widgets
{

class GraphicalComponentBasePrivate;

/**
 * @brief Base for all graphical components
 *
 * This class is used to represent all the informations
 * that a graphical component, that can be a widget,
 * or a dock, have. It an be accessed through QML.
 *
 * These informations are
 * - fileName(), that is the filename of the component.
 * - disambiguation(), that is a disambiguation parameter.
 * - settingsEnabled() that check if this graphical have settings dialog.
 * - settingsFileName(), that is the filename of the settings component for this component.
 *
 * This class can also be serialized to an XML element. This
 * serialization is incomplete, since none of the information
 * from ComponentBase is saved, but this information can still
 * be retrived using the package manager.
 */
class GraphicalComponentBase: public QObject, public XmlSerializableInterface
{
    Q_OBJECT
    /**
     * @short Filename of the component
     */
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
    /**
     * @short Disambiguation parameter of the component
     */
    Q_PROPERTY(QVariantHash disambiguation READ disambiguation NOTIFY disambiguationChanged)
    /**
     * @short If this component have settings
     */
    Q_PROPERTY(bool settingsEnabled READ isSettingsEnabled NOTIFY settingsEnabledChanged)
    /**
     * @short Filename of the settings component of this component
     */
    Q_PROPERTY(QString settingsFileName READ settingsFileName NOTIFY settingsFileNameChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit GraphicalComponentBase(QObject *parent = 0);
    /**
     * @brief Constructor
     *
     * This constructor is used to create a base
     * for graphical components by providing all the
     * informations.
     *
     * @param fileName filename of the component.
     * @param disambiguation disambiguation parameter of the component.
     * @param settingsFileName filename of the settings component.
     * @param parent parent object.
     */
    explicit GraphicalComponentBase(const QString &fileName, const QVariantHash &disambiguation,
                                    const QString &settingsFileName, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~GraphicalComponentBase();
    /**
     * @brief Filename of the component
     * @return filename of the component.
     */
    QString fileName() const;
    /**
     * @brief Disambiguation parameter of the component
     * @return disambiguation parameter of the component.
     */
    QVariantHash disambiguation() const;
    /**
     * @brief If this component have settings
     * @return if this component have settings.
     */
    bool isSettingsEnabled() const;
    /**
     * @brief Filename of the settings component of this component
     * @return filename of the settings component of this component.
     */
    QString settingsFileName() const;
    /**
     * @brief Load from XML element
     * @param elementthe source XML element.
     * @return if the loading succeded.
     */
    virtual bool fromXmlElement(const QDomElement &element);
    /**
     * @brief Save to XML element
     *
     * @param tagName the tag that will be used to create this element.
     * @param document a pointer to the document that is used to create elements.
     * @return the class as an XML element.
     */
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
Q_SIGNALS:
    /**
     * @brief Filename changed
     */
    void fileNameChanged();
    /**
     * @brief Disambiguation changed
     */
    void disambiguationChanged();
    /**
     * @brief Settings enabled changed
     */
    void settingsEnabledChanged();
    /**
     * @brief Settings filename changed
     */
    void settingsFileNameChanged();
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    explicit GraphicalComponentBase(GraphicalComponentBasePrivate *dd, QObject *parent);
    /**
     * @brief Set the filename of the component
     * @param fileName filename of the component.
     */
    void setFileName(const QString &fileName);
    /**
     * @brief Set the disambiguation parameter of the component
     * @param disambiguation disambiguation parameter of the component.
     */
    void setDisambiguation(const QVariantHash &disambiguation);
    /**
     * @brief Set the filename of the settings component of this component
     * @param settingsFileName filename of the settings component of this component.
     */
    void setSettingsFileName(const QString &settingsFileName);
    /**
     * @brief D-pointer
     */
    QScopedPointer <GraphicalComponentBasePrivate> d_pointer;
private:
    W_DECLARE_PRIVATE(GraphicalComponentBase)
};

}

#endif // WIDGETS_GRAPHICALCOMPONENTBASE_H
