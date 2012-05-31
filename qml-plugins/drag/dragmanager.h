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

#ifndef WIDGETS_DRAG_DRAGMANAGER_H
#define WIDGETS_DRAG_DRAGMANAGER_H

#include <QtCore/QObject>

class QDeclarativeContext;
namespace Widgets
{

namespace Drag
{

class DragManagerPrivate;
class DragManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged)
public:
    explicit DragManager(QObject *parent = 0);
    virtual ~DragManager();
    void setContext(QDeclarativeContext *context);
    bool locked() const;
signals:
    void lockedChanged();
public slots:
    void load();
    void setLocked(bool locked);
protected:
    const QScopedPointer<DragManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DragManager)
};

}

}

#endif // WIDGETS_DRAG_DRAGMANAGER_H
