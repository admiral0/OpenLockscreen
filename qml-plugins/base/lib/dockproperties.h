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

#ifndef WIDGETS_DOCKPROPERTIES_H
#define WIDGETS_DOCKPROPERTIES_H

#include "dockbaseproperties.h"

#include <QtCore/QMetaType>
#include <QtCore/QVariantMap>

#include "identifiedelementinterface.h"

namespace Widgets
{

class DockPropertiesPrivate;
class DockProperties: public DockBaseProperties, private IdentifiedElementInterface
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier NOTIFY identifierChanged)
    Q_PROPERTY(QVariantMap settings READ settings NOTIFY settingsChanged)
public:
    explicit DockProperties(QObject *parent = 0);
    explicit DockProperties(const QString &fileName, const QString &packageIdentifier,
                            bool settingsEnabled,
                            int width, int height,
                            bool anchorsTop, bool anchorsBottom,
                            bool anchorsLeft, bool anchorsRight,
                            const QVariantMap &settings = QVariantMap(),
                            QObject *parent = 0);
    explicit DockProperties(const QString &fileName, const QString &packageIdentifier,
                            bool settingsEnabled,
                            int width, int height,
                            bool anchorsTop, bool anchorsBottom,
                            bool anchorsLeft, bool anchorsRight,
                            const  QString &identifier,
                            const QVariantMap &settings = QVariantMap(),
                            QObject *parent = 0);
    QString identifier() const;
    QVariantMap settings() const;
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
public Q_SLOTS:
    void setSettings(const QVariantMap &settings);
Q_SIGNALS:
    void identifierChanged(const QString &identifier);
    void settingsChanged(const QVariantMap &settings);
protected:
    DockProperties(DockPropertiesPrivate *dd, QObject *parent);
    void setIdentifier(const QString &identifier);
private:
    W_DECLARE_PRIVATE(DockProperties)
};

}

Q_DECLARE_METATYPE(Widgets::DockProperties *)

#endif // WIDGETS_DOCKPROPERTIES_H
