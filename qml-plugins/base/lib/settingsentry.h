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

/**
 * @file settingsentry.h
 * @short Definition of Widgets::SettingsEntry
 */

#include <QtCore/QObject>
#include <QtCore/QVariant>

namespace Widgets
{

class SettingsEntryPrivate;

/**
 * @brief An entry in Settings
 *
 * This container class is used to provide default settings
 * entries in Settings. It is available in QML, and should be
 * provided as lists, to the Settings::defaultSettings property.
 */
class SettingsEntry : public QObject
{
    Q_OBJECT
    /**
     * @short Group of the settings entry
     */
    Q_PROPERTY(QString group READ group WRITE setGroup NOTIFY groupChanged)
    /**
     * @short Key of the settings entry
     */
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    /**
     * @short Value of the settings entry
     */
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit SettingsEntry(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~SettingsEntry();
    /**
     * @brief Group of the settings entry
     * @return group of the settings entry.
     */
    QString group() const;
    /**
     * @short Key of the settings entry
     * @return key of the settings entry.
     */
    QString key() const;
    /**
     * @brief Value of the settings entry
     * @return value of the settings entry.
     */
    QVariant value() const;
Q_SIGNALS:
    /**
     * @brief Group changed
     */
    void groupChanged();
    /**
     * @brief Key changed
     */
    void keyChanged();
    /**
     * @brief Value changed
     */
    void valueChanged();
public Q_SLOTS:
    /**
     * @brief Set the group of the settings entry
     * @param group group of the settings entry.
     */
    void setGroup(const QString &group);
    /**
     * @brief Set the key of the settings entry
     * @param key key of the settings entry.
     */
    void setKey(const QString &key);
    /**
     * @brief Set the value of the settings entry
     * @param value value of the settings entry.
     */
    void setValue(const QVariant &value);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    SettingsEntry(SettingsEntryPrivate *dd, QObject *parent);
    /**
     * @brief D-pointer
     */
    const QScopedPointer<SettingsEntryPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(SettingsEntry)

};

}

#endif // WIDGETS_SETTINGSENTRY_H
