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

#include <QtCore/QObject>

#include "xmlserializableinterface.h"
#include "componentbase.h"

namespace Widgets
{

class GraphicalComponentBasePrivate;

/**
 * @brief Base for all graphical components
 *
 * This class is used to represent all the informations
 * that a graphical component, that is, either a widget,
 * or a dock, have. It an be accessed through QML.
 *
 * These informations are
 * - fileName(), that is the filename of the component.
 * - packageIdentifier(), that is the identifier of the package that this component
 *   belongs to.
 * - settingsEnabled() that is WIP
 * @todo manage settingsEnabled().
 *
 * This class can also be serialized to an XML element. This
 * serialization is incomplete, since none of the information
 * from ComponentBase is saved, but this information can still
 * be retrived using the package manager.
 *
 * The page about \ref packageCreationMetaSubsection "desktop file creation" provides more
 * information about how desktop files should be written.
 *
 * @see Widgets::PackageManager.
 */
class GraphicalComponentBase: public ComponentBase, public XmlSerializableInterface
{
    Q_OBJECT
    /**
     * @short Filename of the component
     */
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
    /**
     * @short Package idenfifier of the component
     */
    Q_PROPERTY(QString packageIdentifier READ packageIdentifier NOTIFY packageIdentifierChanged)
    /**
     * @short Settings enabled
     * @todo pay attention to this
     */
    Q_PROPERTY(bool settingsEnabled READ isSettingsEnabled NOTIFY settingsEnabledChanged)
    Q_PROPERTY(QString settingsFileName READ settingsFileName NOTIFY settingsFileNameChanged)
public:
    explicit GraphicalComponentBase(QObject *parent = 0);
    explicit GraphicalComponentBase(const QString &fileName, const QString &packageIdentifier,
                                    const QString &settingsFileName, QObject *parent = 0);
    virtual ~GraphicalComponentBase();
    QString fileName() const;
    QString packageIdentifier() const;
    bool isSettingsEnabled() const;
    QString settingsFileName() const;
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
Q_SIGNALS:
    void fileNameChanged(const QString &fileName);
    void packageIdentifierChanged(const QString &packageIdentifier);
    void settingsEnabledChanged();
    void settingsFileNameChanged() const;
protected:
    explicit GraphicalComponentBase(GraphicalComponentBasePrivate *dd, QObject *parent);
    void setFileName(const QString &fileName);
    void setPackageIdentifier(const QString &packageIdentifier);
    void setSettingsFileName(const QString &settingsFileName);
private:
    W_DECLARE_PRIVATE(GraphicalComponentBase)
};

}

#endif // WIDGETS_GRAPHICALCOMPONENTBASE_H
