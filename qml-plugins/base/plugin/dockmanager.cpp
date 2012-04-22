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

#include "dockmanager.h"

#include <QtCore/QDebug>

#include "dockproperties.h"

namespace Widgets
{

class DockManagerPrivate
{
public:
    DockManagerPrivate(DockManager *q);
    void slotRecomputeMargins();
    DockModel *dockModel;
    int topMargin;
    int bottomMargin;
    int leftMargin;
    int rightMargin;
private:
    DockManager * const q_ptr;
    Q_DECLARE_PUBLIC(DockManager)
};

DockManagerPrivate::DockManagerPrivate(DockManager *q):
    q_ptr(q)
{
    dockModel = 0;
}

void DockManagerPrivate::slotRecomputeMargins()
{
    Q_Q(DockManager);
    topMargin = 0;
    bottomMargin = 0;
    leftMargin = 0;
    rightMargin = 0;

    if (dockModel == 0) {
        return;
    }

    for (int i = 0; i < dockModel->count(); i++) {
        QVariant dockVariant = dockModel->data(dockModel->index(i), DockModel::DockRole);
        DockProperties * dock = dockVariant.value<DockProperties *>();

        // Dock has width set
        if (dock->width() > 0 && dock->height() <= 0) {
            if (dock->anchorsLeft()) {
                leftMargin = qMax(leftMargin, dock->width());
            }
            if (dock->anchorsRight()) {
                rightMargin = qMax(rightMargin, dock->width());
            }
        }

        // Dock has height set
        if (dock->width() <= 0 && dock->height() > 0) {
            if (dock->anchorsTop()) {
                topMargin = qMax(topMargin, dock->height());
            }
            if (dock->anchorsBottom()) {
                bottomMargin = qMax(bottomMargin, dock->height());
            }
        }
    }
    emit q->topMarginChanged(topMargin);
    emit q->bottomMarginChanged(bottomMargin);
    emit q->leftMarginChanged(leftMargin);
    emit q->rightMarginChanged(rightMargin);
}

////// End of private class //////

DockManager::DockManager(QObject *parent) :
    QObject(parent), d_ptr(new DockManagerPrivate(this))
{
}

DockManager::~DockManager()
{
}

DockModel * DockManager::dockModel() const
{
    Q_D(const DockManager);
    return d->dockModel;
}

int DockManager::topMargin() const
{
    Q_D(const DockManager);
    return d->topMargin;
}

int DockManager::bottomMargin() const
{
    Q_D(const DockManager);
    return d->bottomMargin;
}

int DockManager::leftMargin() const
{
    Q_D(const DockManager);
    return d->leftMargin;
}

int DockManager::rightMargin() const
{
    Q_D(const DockManager);
    return d->rightMargin;
}

void DockManager::setDockModel(DockModel *dockModel)
{
    Q_D(DockManager);
    if (d->dockModel != dockModel) {
        d->dockModel = dockModel;
        emit dockModelChanged();

        connect(dockModel, SIGNAL(countChanged(int)), this, SLOT(slotRecomputeMargins()));
        d->slotRecomputeMargins();
    }
}

}

#include "moc_dockmanager.cpp"
