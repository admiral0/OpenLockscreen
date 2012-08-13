/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef WIDGETS_DRAG_DRAGPARAMETERS_H
#define WIDGETS_DRAG_DRAGPARAMETERS_H

/**
 * @file dragparameters.h
 * @short Definition of Widgets::Drag::DragParameters
 */

#include <QtCore/QObject>

namespace Widgets
{

namespace Drag
{

class DragParametersPrivate;

/**
 * @brief Parameters for draggers
 *
 * This class is used to provide some parameters that are
 * used in the drag plugin. They are used as a global variable
 * to store these parameters, and make them available to all
 * draggers.
 *
 * These parameters are related to the source of the image that
 * is used in the draggers. They are available as properties.
 * These properties are
 * - removeButtonSource()
 * - editButtonSource()
 */
class DragParameters : public QObject
{
    Q_OBJECT
    /**
     * @short Remove button source
     */
    Q_PROPERTY(QString removeButtonSource READ removeButtonSource WRITE setRemoveButtonSource
               NOTIFY removeButtonSourceChanged)
    /**
     * @short Edit button source
     */
    Q_PROPERTY(QString editButtonSource READ editButtonSource WRITE setEditButtonSource
               NOTIFY editButtonSourceChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit DragParameters(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DragParameters();
    /**
     * @brief Remove button source
     * @return return button source.
     */
    QString removeButtonSource() const;
    /**
     * @brief Edit button source
     * @return edit button source.
     */
    QString editButtonSource() const;
Q_SIGNALS:
    /**
     * @brief Remove button source changed
     */
    void removeButtonSourceChanged();
    /**
     * @brief Edit button source changed
     */
    void editButtonSourceChanged();
public slots:
    /**
     * @brief Set the remove button source
     * @param removeButtonSource remove button source.
     */
    void setRemoveButtonSource(const QString &removeButtonSource);
    /**
     * @brief Set the edit button source
     * @param editButtonSource edit button source.
     */
    void setEditButtonSource(const QString &editButtonSource);
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<DragParametersPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DragParameters)
};

}

}

#endif // WIDGETS_DRAG_DRAGPARAMETERS_H
