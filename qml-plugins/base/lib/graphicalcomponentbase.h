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
 * Please note that all the filename should not be path.
 * The role of providers is to be capable of retrieving
 * file path from filenames.
 */
class GraphicalComponentBase: public QObject
{
    Q_OBJECT
    /**
     * @short Filename of the component
     */
    Q_PROPERTY(QString fileName READ fileName CONSTANT)
    /**
     * @short Disambiguation parameter of the component
     */
    Q_PROPERTY(QVariantHash disambiguation READ disambiguation CONSTANT)
    /**
     * @short If this component have settings
     */
    Q_PROPERTY(bool settingsEnabled READ isSettingsEnabled CONSTANT)
    /**
     * @short Filename of the settings component of this component
     */
    Q_PROPERTY(QString settingsFileName READ settingsFileName CONSTANT)
public:
    /**
     * @brief Default constructor
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
Q_SIGNALS:
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    explicit GraphicalComponentBase(GraphicalComponentBasePrivate *dd, QObject *parent);
    /**
     * @brief D-pointer
     */
    QScopedPointer <GraphicalComponentBasePrivate> d_pointer;
private:
    W_DECLARE_PRIVATE(GraphicalComponentBase)
};

}

#endif // WIDGETS_GRAPHICALCOMPONENTBASE_H
