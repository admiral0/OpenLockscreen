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
 * @file applicationsmodel.h
 * @short Definition of Mobile::Launcher::ApplicationsModel
 *
 * This file contains the definition of the
 * Widgets::ApplicationsModel class.
 */

#ifndef MOBILE_LAUNCHER_APPLICATIONSMODEL_H
#define MOBILE_LAUNCHER_APPLICATIONSMODEL_H

#include "foldermodel.h"

namespace Mobile
{

namespace Launcher
{

class ApplicationsModelPrivate;
/**
 * @short Model for applications launcher
 *
 * This class is the model that manages the content
 * of the applications launcher.
 *
 * This class is responsible of populating the parent
 * FolderModel. It parse contents of configuration
 * file to find the applications to display, and
 * populates both folder and subfolders.
 */
class ApplicationsModel: public FolderModel
{
    Q_OBJECT
public:
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit ApplicationsModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~ApplicationsModel();
public Q_SLOTS:
    void update();
private:
    Q_DECLARE_PRIVATE(ApplicationsModel)
};

}

}

#endif // MOBILE_LAUNCHER_APPLICATIONSMODEL_H
