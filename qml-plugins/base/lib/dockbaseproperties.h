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

#ifndef WIDGETS_DOCKBASEPROPERTIES_H
#define WIDGETS_DOCKBASEPROPERTIES_H

#include "graphicalelementbaseproperties.h"

namespace Widgets
{

class DockBasePropertiesPrivate;
class DockBaseProperties: public GraphicalElementBaseProperties
{
    Q_OBJECT
    /**
     * @short Width of the dock
     */
    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    /**
     * @short Height of the dock
     */
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    /**
     * @short If the dock is anchored using top anchor
     */
    Q_PROPERTY(bool anchorsTop READ anchorsTop CONSTANT)
    /**
     * @short If the dock is anchored using bottom anchor
     */
    Q_PROPERTY(bool anchorsBottom READ anchorsBottom CONSTANT)
    /**
     * @short If the dock is anchored using left anchor
     */
    Q_PROPERTY(bool anchorsLeft READ anchorsLeft CONSTANT)
    /**
     * @short If the dock is anchored using right anchor
     */
    Q_PROPERTY(bool anchorsRight READ anchorsRight CONSTANT)
public:
    explicit DockBaseProperties(QObject *parent = 0);
    explicit DockBaseProperties(const QString &name, const QString &packageName,
                                /*const QString &qmlFile,*/ bool settingsEnabled,
                                int width, int height,
                                bool anchorsTop, bool anchorsBottom,
                                bool anchorsLeft, bool anchorsRight,
                                QObject *parent = 0);
    bool isValid() const;
    int width() const;
    int height() const;
    bool anchorsTop() const;
    bool anchorsBottom() const;
    bool anchorsLeft() const;
    bool anchorsRight() const;
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    static DockBaseProperties * fromDesktopFile(const QString &file, QObject *parent = 0);
Q_SIGNALS:
    void widthChanged(int width);
    void heightChanged(int height);
    void anchorsTopChanged(bool anchorsTop);
    void anchorsBottomChanged(bool anchorsBottom);
    void anchorsLeftChanged(bool anchorsLeft);
    void anchorsRightChanged(bool anchorsRight);
protected:
    DockBaseProperties(DockBasePropertiesPrivate *dd, QObject *parent);
    void setWidth(int width);
    void setHeight(int height);
    void setAnchorsTop(bool anchorsTop);
    void setAnchorsBottom(bool anchorsBottom);
    void setAnchorsLeft(bool anchorsLeft);
    void setAnchorsRight(bool anchorsRight);
private:
    explicit DockBaseProperties(const QString &file, QObject *parent = 0);
    Q_DECLARE_PRIVATE(DockBaseProperties)
};

}

#endif // WIDGETS_DOCKBASEPROPERTIES_H
