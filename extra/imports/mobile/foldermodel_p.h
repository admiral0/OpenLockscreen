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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file foldermodel_p.h
 * @short Definition of Mobile::Launcher::FolderModelPrivate
 */

#ifndef WIDGETS_MOBILEEXTRA_FOLDERMODEL_P_H
#define WIDGETS_MOBILEEXTRA_FOLDERMODEL_P_H

#include <QtCore/QAbstractListModel>

namespace Mobile
{

namespace Launcher
{

class FolderModelItem;
/**
 * @internal
 * @short Private class for Widgets::MobileExtra::FolderModel
 */
class FolderModelPrivate
{
public:
    /**
     * @internal
     * @short Destructor
     */
    ~FolderModelPrivate();
    /**
     * @internal
     * @short Helper method used to delete FolderModelItem
     *
     * @param item the FolderModelItem to delete.
     */
    void deleteItem(FolderModelItem * item);
    /**
     * @internal
     * @short Data
     */
    QList<FolderModelItem *> data;
};

}

}

#endif // WIDGETS_MOBILEEXTRA_FOLDERMODEL_H
