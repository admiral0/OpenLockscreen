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

/**
 * @file applicationinformations.h
 * @short Definition of ApplicationInformations
 */

#ifndef WIDGETS_APPLICATIONINFORMATIONS_H
#define WIDGETS_APPLICATIONINFORMATIONS_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>

/**
 * @short Application informations
 *
 * This class is used to store informations
 * about an application.
 *
 * This class stores these properties
 * - name of the application
 * - path to the icon of the application
 * - command line used to run the application
 *
 * Each of these properties can be access
 * either using getter methods or using
 * properties, in a QML context.
 *
 * Please note that all the properties
 * are constant and they should be passed
 * through the constructor.
 */
class ApplicationInformations : public QObject
{
    Q_OBJECT
    /**
     * @short Name of the application
     */
    Q_PROPERTY(QString name READ name CONSTANT)
    /**
     * @short Icon of the application
     */
    Q_PROPERTY(QString icon READ icon CONSTANT)
    /**
     * @short Command line used to run the application
     */
    Q_PROPERTY(QString command READ command CONSTANT)
public:
    /**
     * @short Default constructor
     *
     * @param name name of the application.
     * @param icon icon of the application.
     * @param command command line used to run the application.
     * @param parent parent object.
     */
    explicit ApplicationInformations(const QString &name = QString(),
                                     const QString &icon = QString(),
                                     const QString &command = QString(),
                                     QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~ApplicationInformations();
    /**
     * @short Name of the application
     *
     * @return name of the application.
     */
    QString name() const;
    /**
     * @short Icon of the application
     *
     * @return icon of the application.
     */
    QString icon() const;
    /**
     * @short Command line used to run the application
     *
     * @return command line used to run the application.
     */
    QString command() const;
private:
    class ApplicationInformationsPrivate;
    /**
     * @short D-pointer
     */
    ApplicationInformationsPrivate * const d;
};

Q_DECLARE_METATYPE(ApplicationInformations *)

#endif // WIDGETS_APPLICATIONINFORMATIONS_H
