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

#include <QtCore/QObject>

namespace Widgets
{

namespace Drag
{

class DragParametersPrivate;
class DragParameters : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString removeButtonSource READ removeButtonSource WRITE setRemoveButtonSource
               NOTIFY removeButtonSourceChanged)
public:
    explicit DragParameters(QObject *parent = 0);
    virtual ~DragParameters();
    QString removeButtonSource() const;
Q_SIGNALS:
    void removeButtonSourceChanged();
public slots:
    void setRemoveButtonSource(const QString &removeButtonSource);
protected:
    QScopedPointer<DragParametersPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DragParameters)
};

}

}

#endif // WIDGETS_DRAG_DRAGPARAMETERS_H
