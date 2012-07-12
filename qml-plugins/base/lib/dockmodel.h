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

#ifndef WIDGETS_DOCKMODEL_H
#define WIDGETS_DOCKMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>

#include "dockbaseproperties.h"

namespace Widgets
{

class DockModelPrivate;
class DockModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum DisplayedDocksRole {
        /**
         * @short Dock role
         */
        DockRole = Qt::UserRole + 1
    };
    explicit DockModel(QObject *parent = 0);
    virtual ~DockModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int count() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE bool hasDock(const QString &packageIdentifier, const QString &fileName) const;
Q_SIGNALS:
    /**
     * @short Count changed
     *
     * Notify that the row count
     * has changed.
     *
     * @param count value of the new row count.
     */
    void countChanged(int count);
public Q_SLOTS:
    /**
     * @short Add a dock
     *
     * This method is used to add a dock
     * to the model. The dock to add is
     * caracterized by a DockBaseProperties.
     *
     * Missing properties such as identifier and settings
     * are either provided or added by this method.
     *
     * @param dock the dock to add.
     * @param settings settings of the dock to add.
     * @param identifier identifier of the dock to add (only used during loading).
     */
    void addDock(Widgets::DockBaseProperties *dock,
                 const QVariantMap &settings = QVariantMap(),
                 const QString &identifier = QString());
protected:
    DockModel(DockModelPrivate *dd, QObject *parent = 0);
    virtual bool event(QEvent *event);
    const QScopedPointer<DockModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DockModel)
};

}

#endif // WIDGETS_DOCKMODEL_H
