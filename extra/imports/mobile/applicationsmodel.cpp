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
 * @file applicationsmodel.cpp
 * @short Implementation of Mobile::Launcher::ApplicationsModel
 */

#include "applicationsmodel.h"
#include "foldermodel_p.h"
#include "applicationinformations.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QFile>

/// @todo Refresh this model sometimes (otherwise it will not contain all the apps)

namespace Mobile
{

namespace Launcher
{

/**
 * @internal
 * @short LAUNCHER_LAYOUT_PATH
 *
 * Used in Mobile::Launcher::ApplicationsModel.
 */
static const char *LAUNCHER_LAYOUT_PATH =
    "/home/user/.config/meegotouchhome-nokia/launcherbuttons.data";
/**
 * @internal
 * @short BASE_ICON_PATH
 *
 * Used in Mobile::Launcher::ApplicationsModel.
 */
static const char *BASE_ICON_PATH = "/usr/share/themes/base/meegotouch/icons/";
/**
 * @internal
 * @short BASE_SVG_PATH
 *
 * Used in Mobile::Launcher::ApplicationsModel.
 */
static const char *BASE_SVG_PATH = "/usr/share/themes/base/meegotouch/svg/";
/**
 * @internal
 * @short BLANCO_ICON_PATH
 *
 * Used in Mobile::Launcher::ApplicationsModel.
 */
static const char *BLANCO_ICON_PATH = "/usr/share/themes/blanco/meegotouch/icons/";
/**
 * @internal
 * @short DEFAULT_ICON_PATH
 *
 * Used in Mobile::Launcher::ApplicationsModel.
 */
static const char *DEFAULT_ICON_PATH = "/usr/share/icons/hicolor/%1/apps/";

/**
 * @internal
 * @short Private class for ViewWidgetsModel
 */
class ApplicationsModelPrivate: public FolderModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    ApplicationsModelPrivate(ApplicationsModel *q);
    /**
     * @internal
     * @short Initialize the model
     */
    void init();
    /**
     * @internal
     * @short Application informations
     *
     * This method parse a given .desktop file and
     * store all the extracted informations an object.
     *
     * @param desktopFile path to the .desktop file.
     * @return an ApplicationInformations that stores information
     * about the application.
     */
    ApplicationInformations * applicationInformations(const QString &desktopFile);
    /**
     * @internal
     * @short Folder name
     *
     * This method parse a given .folder file and
     * extracts the name of the folder.
     *
     * @param folderFile path to the .folder file.
     * @return name of the folder.
     */
    QString folderName(const QString &folderFile);
    /**
     * @internal
     * @short Find the path of an icon
     *
     * Icons that are not defined with their absolute
     * path can be hidden in different locations.
     *
     * This method is used to retrieve the icon from
     * those different locations and provide an absolute
     * path to the icon.
     *
     * @param iconName name of the icon.
     * @param executable command used to execute the application.
     * @return absolute path to the icon.
     */
    QString findIconPath(const QString &iconName, const QString &executable);
private:
    /**
     * @short Q-pointer
     */
    ApplicationsModel * q_ptr;
    Q_DECLARE_PUBLIC(ApplicationsModel)
};

ApplicationsModelPrivate::ApplicationsModelPrivate(ApplicationsModel *q):
    FolderModelPrivate(), q_ptr(q)
{
}

void ApplicationsModelPrivate::init()
{
    Q_Q(ApplicationsModel);

    // The application tree is a 2 level list.
    // The 1st level is a list of list that contains content of folders
    // The 2nd level is a list of strings that contains path to desktop
    // files. This list is used to get information about folders and launchers
    QList<QStringList>  applicationTree;

    // Open the file with the launcher layout
    QFile file (LAUNCHER_LAYOUT_PATH);
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }

    // RegExps
    QRegExp lineRegExp ("^([\\w\\\\.-]+)=launcher/(\\d+)/(\\d+)\n$");

    // Run through the file
    while (!file.atEnd()) {
        QString line = file.readLine();

        if (line.indexOf(lineRegExp) != -1) {
            QString path = lineRegExp.cap(1);
            int folderNumber = lineRegExp.cap(2).toInt();
            int position = lineRegExp.cap(3).toInt();

            // Check if need to add more folders
            while (applicationTree.count() <= folderNumber) {
                applicationTree.append(QStringList());
            }

            // Check if need to add more items in the folder
            while (applicationTree[folderNumber].count() <= position) {
                applicationTree[folderNumber].append(QString());
            }

            applicationTree[folderNumber][position] = path;
        }

    }

    file.close();

    // applicationTree now stores path to desktop / folder files for all
    // folder and launcher

    // Create folders
    QList<FolderModel *> folders;
    folders.append(q);
    for (int i = 1; i < applicationTree.count(); i++) {
        folders.append(new FolderModel(q));
    }

    // Populate folders
    QRegExp folderRegExp ("folder(\\d+).directory");
    for (int i = 0; i < applicationTree.count(); i++) {
        QListIterator<QString> applicationIterator = QListIterator<QString>(applicationTree[i]);
        while(applicationIterator.hasNext()) {
            // Get desktop file path
            QString desktopFile = applicationIterator.next();
            desktopFile.replace("\\", "/");
            desktopFile.prepend("/");

            // Check if it is a folder or a file
            if (desktopFile.endsWith(".desktop")) {
                ApplicationInformations *informations = applicationInformations(desktopFile);
                if(informations != 0) {
                    folders[i]->addApplication(informations->name(), informations);
                }
            } else if (desktopFile.indexOf(folderRegExp) != -1) {
                int folderIndex = folderRegExp.cap(1).toInt();
                QString name = folderName(desktopFile);
                folders[i]->addSubfolder(name, folders.at(folderIndex));
            }
        }
    }
}

QString ApplicationsModelPrivate::folderName(const QString &folderFile)
{
    if (folderFile.isEmpty()) {
        return QString();
    }

    QFile file (folderFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return QString();
    }

    QString name = QString();

    QRegExp nameRegExp ("Name=(.+)\n$");
    while (!file.atEnd()) {
        QString line = QString::fromUtf8(file.readLine());
        if (nameRegExp.indexIn(line) != -1 && name.isEmpty()) {
            name = nameRegExp.cap(1).trimmed();
        }
    }

    file.close();

    return name;
}

ApplicationInformations * ApplicationsModelPrivate
                          ::applicationInformations(const QString &desktopFile)
{
    Q_Q(ApplicationsModel);

    if (desktopFile.isEmpty()) {
        return 0;
    }

    QFile file (desktopFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return 0;
    }

    // Used to extract the information
    QRegExp iconRegExp ("Icon=(.+)\n$");
    QString iconPath;
    QRegExp nameRegExp ("Name=(.+)\n$");
    QString name;
    QRegExp execRegExp ("Exec=(.+)\n$");
    QString exec;


    while (!file.atEnd()) {
        QString line = file.readLine();
        if (iconRegExp.indexIn(line) != -1  && iconPath.isEmpty()) {
            iconPath = iconRegExp.cap(1).trimmed();
        }

        if (nameRegExp.indexIn(line) != -1 && name.isEmpty()) {
            name = nameRegExp.cap(1).trimmed();
        }

        if (execRegExp.indexIn(line) != -1 && exec.isEmpty()) {
            exec = execRegExp.cap(1).trimmed();
        }
    }

    if (!iconPath.contains("/")) {
        // Icons that are given without directories
        // are either loaded using image://theme/
        // or part of the package.
        // We need to check where do they come from
        iconPath = findIconPath(iconPath, exec);
    }

    file.close();

    // Return
    return new ApplicationInformations(name, iconPath, exec, q);
}



QString ApplicationsModelPrivate::findIconPath(const QString &iconName,
                                               const QString &executable)
{
    // Check if it is in theme directories
    QString iconNamePng = iconName + ".png";
    QString iconNameSvg = iconName + ".svg";
    QDir dirBlanco = QDir(BLANCO_ICON_PATH);
    QDir dirBase = QDir(BASE_ICON_PATH);
    QDir dirSvg = QDir(BASE_SVG_PATH);

    // Check base folders
    if (dirBlanco.exists(iconNamePng)) {
        return dirBlanco.absoluteFilePath(iconNamePng);
    }
    if (dirBlanco.exists(iconNameSvg)) {
        return dirBlanco.absoluteFilePath(iconNamePng);
    }
    if (dirBase.exists(iconNamePng)) {
        return dirBlanco.absoluteFilePath(iconNamePng);
    }
    if (dirBase.exists(iconNameSvg)) {
        return dirBlanco.absoluteFilePath(iconNamePng);
    }
    if (dirSvg.exists(iconNamePng)) {
        return dirBlanco.absoluteFilePath(iconNamePng);
    }
    if (dirSvg.exists(iconNameSvg)) {
        return dirBlanco.absoluteFilePath(iconNamePng);
    }


    // If not, check the default icons folders
    QStringList iconSizes = QStringList();
    iconSizes.append("80x80");
    iconSizes.append("64x64");
    iconSizes.append("48x48");
    QString foundPath = QString();
    int i = 0;
    while (i < iconSizes.count() && foundPath.isEmpty()) {
        // Check a resolution dependant folder
        QDir dir = QDir(QString(DEFAULT_ICON_PATH).arg(iconSizes.at(i)));

        // If the file is found, we retrieve
        // the absolute path to the file
        if (dir.exists(iconNamePng)) {
            foundPath = dir.absoluteFilePath(iconNamePng);
        }
        if (dir.exists(iconNameSvg)) {
            foundPath = dir.absoluteFilePath(iconNameSvg);
        }
        i++;
    }

    if (!foundPath.isEmpty()) {
        return foundPath;
    }

    // If we still failed to found the icon, we have to search
    // in the /opt/<appFolder> folders
    QRegExp appFolderRegExp = QRegExp("(/opt/[^/]+)/");

    if(appFolderRegExp.indexIn(executable) != -1 && !executable.isEmpty()) {
        QString iconFolder = appFolderRegExp.cap(1) + "/images/";
        QDir dir = QDir(iconFolder);
        if (dir.exists(iconNamePng)) {
            return dir.absoluteFilePath(iconNamePng);
        }
        if (dir.exists(iconNameSvg)) {
            return dir.absoluteFilePath(iconNameSvg);
        }
    }


    // Failed to found the icon
    return "/usr/share/themes/blanco/meegotouch/icons/icon-l-default-application.png";
}

////// End of private class //////

ApplicationsModel::ApplicationsModel(QObject *parent):
    FolderModel(new ApplicationsModelPrivate(this), parent)
{
    Q_D(ApplicationsModel);
    d->init();
}

ApplicationsModel::~ApplicationsModel()
{
}

}

}
