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

#ifndef WIDGETS_DOCKS_DOCKEDVIEWMANAGER_H
#define WIDGETS_DOCKS_DOCKEDVIEWMANAGER_H

/**
 * @file dockedviewmanager.h
 * @short Definition of Widgets::Docks::DockedViewManager
 */

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

#include "dockmodel.h"

namespace Widgets
{

namespace Docks
{

class DockedViewManagerPrivate;

/**
 * @brief Manage the docked view
 *
 * This class is used to provide a conveinent QML interface
 * to the model, that is used to calculate the total size that
 * is used by the docks.
 *
 * This size are represented by four margins, that corresponds to
 * the place that the dock takes at the top, bottom, left and right.
 *
 * Note that this manager is automatically attached to the global
 * dock model, and when the dock model is updated, the informations
 * in this class are automatically recomputed.
 */
class DockedViewManager : public QObject
{
    Q_OBJECT
    /**
     * @short Top margin
     */
    Q_PROPERTY(int topMargin READ topMargin NOTIFY topMarginChanged)
    /**
     * @short Bottom margin
     */
    Q_PROPERTY(int bottomMargin READ bottomMargin NOTIFY bottomMarginChanged)
    /**
     * @short Left margin
     */
    Q_PROPERTY(int leftMargin READ leftMargin NOTIFY leftMarginChanged)
    /**
     * @short Right margin
     */
    Q_PROPERTY(int rightMargin READ rightMargin NOTIFY rightMarginChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit DockedViewManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~DockedViewManager();
    /**
     * @brief Set the dock model
     * @param dockModel the dock model to set.
     */
    void setDockModel(DockModel *dockModel);
    /**
     * @brief Top margin
     * @return top margin.
     */
    int topMargin() const;
    /**
     * @brief Bottom margin
     * @return bottom margin.
     */
    int bottomMargin() const;
    /**
     * @brief Left margin
     * @return left margin.
     */
    int leftMargin() const;
    /**
     * @brief Right margin
     * @return right margin.
     */
    int rightMargin() const;
Q_SIGNALS:
    /**
     * @brief Top margin changed
     */
    void topMarginChanged();
    /**
     * @brief Bottom margin changed
     */
    void bottomMarginChanged();
    /**
     * @brief Left margin changed
     */
    void leftMarginChanged();
    /**
     * @brief Right margin changed
     */
    void rightMarginChanged();
protected:
    /**
     * @brief D-pointer
     */
    const QScopedPointer<DockedViewManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DockedViewManager)
    Q_PRIVATE_SLOT(d_func(), void recomputeMargins())
};

}

}

#endif // WIDGETS_DOCKMANAGER_H
