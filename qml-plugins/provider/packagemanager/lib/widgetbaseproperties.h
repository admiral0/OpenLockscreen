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

#ifndef WIDGETS_WIDGETBASEPROPERTIES_H
#define WIDGETS_WIDGETBASEPROPERTIES_H

#include "graphicalcomponentbase.h"

#include <QtCore/QMetaType>

namespace Widgets
{

class WidgetBasePropertiesPrivate;
class WidgetBaseProperties: public GraphicalComponentBase
{
    Q_OBJECT
    /**
     * @short Minimum width of the dock
     */
    Q_PROPERTY(int minimumWidth READ minimumWidth NOTIFY minimumWidthChanged)
    /**
     * @short Minimum height of the dock
     */
    Q_PROPERTY(int minimumHeight READ minimumHeight NOTIFY minimumHeightChanged)
    /**
     * @short Maximum width of the dock
     */
    Q_PROPERTY(int maximumWidth READ maximumWidth NOTIFY maximumWidthChanged)
    /**
     * @short Maximum height of the dock
     */
    Q_PROPERTY(int maximumHeight READ maximumHeight NOTIFY maximumHeightChanged)
public:
    explicit WidgetBaseProperties(QObject *parent = 0);
    bool isValid() const;
    int minimumWidth() const;
    int minimumHeight() const;
    int maximumWidth() const;
    int maximumHeight() const;
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    static WidgetBaseProperties * fromDesktopFile(const QString &desktopFile,
                                                  const QString &packageIdentifier,
                                                  QObject *parent = 0);
Q_SIGNALS:
    void minimumWidthChanged(int width);
    void minimumHeightChanged(int height);
    void maximumWidthChanged(int width);
    void maximumHeightChanged(int height);
protected:
    explicit WidgetBaseProperties(const QString &fileName, const QString &packageIdentifier,
                                  const QString &settingsFileName,
                                  int width, int height,
                                  QObject *parent = 0);
    explicit WidgetBaseProperties(WidgetBasePropertiesPrivate *dd, QObject *parent);
    void setMinimumWidth(int width);
    void setMinimumHeight(int height);
    void setMaximumWidth(int width);
    void setMaximumHeight(int height);
    friend class PackageManager;
private:
    explicit WidgetBaseProperties(const QString &desktopFile,
                                  const QString &packageIdentifier,
                                  QObject *parent = 0);
    W_DECLARE_PRIVATE(WidgetBaseProperties)
};

}

Q_DECLARE_METATYPE(Widgets::WidgetBaseProperties *)


#endif // WIDGETS_WIDGETBASEPROPERTIES_H
