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
 * @file dockedviewmanager.cpp
 * @short Implementation of Widgets::Docks::DockedViewManager
 */

#include "dockedviewmanager.h"

#include <QtCore/QDebug>

#include "dockproperties.h"

namespace Widgets
{

namespace Docks
{

/**
 * @internal
 * @brief Private class for Widgets::Docks::DockedViewManager
 */
class DockedViewManagerPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer.
     */
    DockedViewManagerPrivate(DockedViewManager *q);
    /**
     * @internal
     * @brief Recompute margins
     */
    void recomputeMargins();
    /**
     * @internal
     * @brief Dock model
     */
    DockModel *dockModel;
    /**
     * @internal
     * @short Top margin
     */
    int topMargin;
    /**
     * @internal
     * @short Bottom margin
     */
    int bottomMargin;
    /**
     * @internal
     * @short Left margin
     */
    int leftMargin;
    /**
     * @internal
     * @short Right margin
     */
    int rightMargin;
private:
    /**
     * @internal
     * @brief Q-pointer
     */
    DockedViewManager * const q_ptr;
    Q_DECLARE_PUBLIC(DockedViewManager)
};

DockedViewManagerPrivate::DockedViewManagerPrivate(DockedViewManager *q):
    q_ptr(q)
{
    dockModel = 0;
}

void DockedViewManagerPrivate::recomputeMargins()
{
    Q_Q(DockedViewManager);

    int oldTopMargin = topMargin;
    int oldBottomMargin = bottomMargin;
    int oldLeftMargin = leftMargin;
    int oldRightMargin = rightMargin;

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

    if (topMargin != oldTopMargin) {
        emit q->topMarginChanged();
    }
    if (bottomMargin != oldBottomMargin) {
        emit q->bottomMarginChanged();
    }
    if (leftMargin != oldLeftMargin) {
        emit q->leftMarginChanged();
    }
    if (rightMargin != oldRightMargin) {
        emit q->rightMarginChanged();
    }
}

////// End of private class //////

DockedViewManager::DockedViewManager(QObject *parent) :
    QObject(parent), d_ptr(new DockedViewManagerPrivate(this))
{
}

DockedViewManager::~DockedViewManager()
{
}

void DockedViewManager::setDockModel(DockModel *dockModel)
{
    Q_D(DockedViewManager);
    if (d->dockModel != dockModel) {
        d->dockModel = dockModel;

        connect(dockModel, SIGNAL(countChanged(int)), this, SLOT(recomputeMargins()));
        d->recomputeMargins();
    }
}

int DockedViewManager::topMargin() const
{
    Q_D(const DockedViewManager);
    return d->topMargin;
}

int DockedViewManager::bottomMargin() const
{
    Q_D(const DockedViewManager);
    return d->bottomMargin;
}

int DockedViewManager::leftMargin() const
{
    Q_D(const DockedViewManager);
    return d->leftMargin;
}

int DockedViewManager::rightMargin() const
{
    Q_D(const DockedViewManager);
    return d->rightMargin;
}

}

}

#include "moc_dockedviewmanager.cpp"
