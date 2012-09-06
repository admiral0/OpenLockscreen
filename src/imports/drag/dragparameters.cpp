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

/**
 * @file dragparameters.cpp
 * @short Implementation of Widgets::Drag::DragParameters
 */

#include "dragparameters.h"

namespace Widgets
{

namespace Drag
{

/**
 * @internal
 * @brief Private class for Widgets::Drag::DragParameters
 */
class DragParametersPrivate
{
public:
    /**
     * @internal
     * @brief Remove button source
     */
    QString removeButtonSource;
    /**
     * @internal
     * @brief Edit button source
     */
    QString editButtonSource;
    /**
     * @internal
     * @brief Resize button source
     */
    QString resizeButtonSource;
};

////// End of private class //////

DragParameters::DragParameters(QObject *parent) :
    QObject(parent), d_ptr(new DragParametersPrivate())
{
}

DragParameters::~DragParameters()
{
}

QString DragParameters::removeButtonSource() const
{
    Q_D(const DragParameters);
    return d->removeButtonSource;
}

QString DragParameters::editButtonSource() const
{
    Q_D(const DragParameters);
    return d->editButtonSource;
}

QString DragParameters::resizeButtonSource() const
{
    Q_D(const DragParameters);
    return d->resizeButtonSource;
}

void DragParameters::setRemoveButtonSource(const QString &removeButtonSource)
{
    Q_D(DragParameters);
    if (d->removeButtonSource != removeButtonSource) {
        d->removeButtonSource = removeButtonSource;
        emit removeButtonSourceChanged();
    }
}

void DragParameters::setEditButtonSource(const QString &editButtonSource)
{
    Q_D(DragParameters);
    if (d->editButtonSource != editButtonSource) {
        d->editButtonSource = editButtonSource;
        emit editButtonSourceChanged();
    }
}

void DragParameters::setResizeButtonSource(const QString &resizeButtonSource)
{
    Q_D(DragParameters);
    if (d->removeButtonSource != resizeButtonSource) {
        d->resizeButtonSource = resizeButtonSource;
        emit resizeButtonSourceChanged();
    }
}

}

}
