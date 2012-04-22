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

#ifndef WIDGETS_COMPONENTBASE_H
#define WIDGETS_COMPONENTBASE_H

#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "widgets_global.h"

namespace Widgets
{

class ComponentBasePrivate;
class ComponentBase: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString defaultName READ defaultName NOTIFY defaultNameChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString defaultDescription READ defaultDescription NOTIFY defaultDescriptionChanged)
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
public:
    explicit ComponentBase(QObject *parent = 0);
    virtual ~ComponentBase();
    bool isValid() const;
    QString icon() const;
    QStringList languages() const;
    QString defaultName() const;
    QString name() const;
    QString name(const QString &language) const;
    QString defaultDescription() const;
    QString description() const;
    QString description(const QString &language) const;
Q_SIGNALS:
    void iconChanged();
    void defaultNameChanged();
    void nameChanged();
    void defaultDescriptionChanged();
    void descriptionChanged();
protected:
    ComponentBase(ComponentBasePrivate * dd, QObject *parent = 0);
    void setIcon(const QString &icon);
    void setDefaultName(const QString &name);
    void addName(const QString &language, const QString &name);
    void setDefaultDescription(const QString &description);
    void addDescription(const QString &language, const QString &description);
    void clearNamesAndDescriptions();
    const QScopedPointer<ComponentBasePrivate> d_pointer;
private:
    W_DECLARE_PRIVATE(ComponentBase)

};

QDebug operator<<(QDebug debug, ComponentBase *component);

}

#endif // WIDGETS_COMPONENTBASE_H
