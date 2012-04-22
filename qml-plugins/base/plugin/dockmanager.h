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

#ifndef WIDGETS_DOCKMANAGER_H
#define WIDGETS_DOCKMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

#include "dockmodel.h"

namespace Widgets
{

class DockManagerPrivate;
class DockManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Widgets::DockModel *dockModel READ dockModel WRITE setDockModel
               NOTIFY dockModelChanged)
    Q_PROPERTY(int topMargin READ topMargin NOTIFY topMarginChanged)
    Q_PROPERTY(int bottomMargin READ bottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(int leftMargin READ leftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(int rightMargin READ rightMargin NOTIFY rightMarginChanged)
public:
    explicit DockManager(QObject *parent = 0);
    virtual ~DockManager();
    DockModel * dockModel() const;
    int topMargin() const;
    int bottomMargin() const;
    int leftMargin() const;
    int rightMargin() const;
public Q_SLOTS:
    void setDockModel(DockModel *dockModel);
Q_SIGNALS:
    void dockModelChanged();
    void topMarginChanged(int topMargin);
    void bottomMarginChanged(int bottomMargin);
    void leftMarginChanged(int leftMargin);
    void rightMarginChanged(int rightMargin);
protected:
    const QScopedPointer<DockManagerPrivate> d_ptr;
    
private:
    Q_DECLARE_PRIVATE(DockManager)
    Q_PRIVATE_SLOT(d_func(), void slotRecomputeMargins())
};

}

#endif // WIDGETS_DOCKMANAGER_H
