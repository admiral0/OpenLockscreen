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

#ifndef WIDGETS_GRAPHICALELEMENTBASEPROPERTIES_H
#define WIDGETS_GRAPHICALELEMENTBASEPROPERTIES_H

#include <QtCore/QObject>
#include "xmlserializableinterface.h"

namespace Widgets
{

class GraphicalElementBasePropertiesPrivate;
class GraphicalElementBaseProperties : public QObject, public XmlSerializableInterface
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString packageName READ packageName CONSTANT)
    Q_PROPERTY(QString qmlFile READ qmlFile CONSTANT)
    Q_PROPERTY(bool hasSettings READ hasSettings CONSTANT)
public:
    explicit GraphicalElementBaseProperties(QObject *parent = 0);
    explicit GraphicalElementBaseProperties(const QString &name, const QString &packageName,
                                            const QString &qmlFile, bool hasSettings);
    virtual ~GraphicalElementBaseProperties();
    QString name() const;
    QString packageName() const;
    QString qmlFile() const;
    bool hasSettings() const;
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
protected:
    const QScopedPointer<GraphicalElementBasePropertiesPrivate> d_ptr;
    GraphicalElementBaseProperties(GraphicalElementBasePropertiesPrivate *dd, QObject *parent);
private:
    Q_DECLARE_PRIVATE(GraphicalElementBaseProperties)
};

}

#endif // WIDGETS_GRAPHICALELEMENTBASEPROPERTIES_H
