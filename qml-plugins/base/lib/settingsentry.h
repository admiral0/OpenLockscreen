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

#ifndef WIDGETS_SETTINGSENTRY_H
#define WIDGETS_SETTINGSENTRY_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace Widgets
{

class SettingsEntryPrivate;
class SettingsEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit SettingsEntry(QObject *parent = 0);
    virtual ~SettingsEntry();
    QString key() const;
    QVariant value() const;
Q_SIGNALS:
    void keyChanged(const QString &key);
    void valueChanged(const QVariant &value);
public Q_SLOTS:
    void setKey(const QString &key);
    void setValue(const QVariant &value);
protected:
    SettingsEntry(SettingsEntryPrivate * dd, QObject *parent);
    const QScopedPointer<SettingsEntryPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(SettingsEntry)
    
};

}

#endif // WIDGETS_SETTINGSENTRY_H
