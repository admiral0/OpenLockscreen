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

#ifndef WIDGETS_DOCKS_DOCKMODEL_H
#define WIDGETS_DOCKS_DOCKMODEL_H

/**
 * @file dockmodel.h
 * @short Definition of Widgets::Docks::DockModel
 */

#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>

class QDeclarativeContext;
namespace Widgets
{

namespace Docks
{

class DockBaseProperties;
class DockProperties;
class DockModelPrivate;

/**
 * @short Model for docks
 *
 * This class is the model that manages all the docks
 * like their settings, and their anchoring.
 *
 * Each item of this model is a Widgets::Docks::DockProperties
 * that is used to control all the parameters
 * related to displayed docks.
 *
 * Modifying this model can be done using
 * - addDock()
 * - removeDock()
 *
 * The first build a Widgets::Docks::DockProperties based
 * on a Widgets::Docks::DockBaseProperties and assign
 * given properties to the new parameters.
 * The second removes a widget based on a
 * Widgets::Docks::DockProperties.
 *
 * Please note that Widgets::Docks::DockProperties objects
 * created with addDock are automatically linked to
 * the real QML widget, and also to settings. If the properties
 * this object are changed, they will automatically be reflected
 * in a graphical change and saved.
 *
 * This class save settings as XML files. They are stored as
 * settings-dock.xml, using QDesktopServices::DataLocation.
 * Loading the settings is done when calling load(). Saving is
 * managed automatically, when widgets changes, are added or
 * removed.
 */
class DockModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum DockModelRole
    {
        DockRole = Qt::UserRole + 1
    };
    /**
     * @short Default constructor
     * @param parent parent object.
     */
    explicit DockModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~DockModel();
    /**
     * @brief Set context
     *
     * This method is only used during initialization,
     * to search for the provider manager. This method
     * uses the QML context to search for this manager.
     *
     * Be sure that the manager is already initialized.
     * This can be done by importing the base module first.
     *
     * @param context QML context.
     */
    void setContext(QDeclarativeContext *context);
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return the number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Count
     * @return count.
     */
    int count() const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /**
     * @short Check if the model already have a dock
     *
     * This method can be useful if you want only one dock of
     * each type to be stored in this model. This method is used
     * to return if the model already have the dock.
     *
     * @param fileName the dock filename.
     * @param disambiguation disambiguation parameter.
     * @return if this model have the dock.
     */
    Q_INVOKABLE bool hasDock(const QString &fileName, const QVariantHash &disambiguation) const;
public Q_SLOTS:
    /**
     * @brief Load
     *
     * Load settings from the XML settings file.
     */
    void load();
    /**
     * @short Add a dock
     * @param dock base properties of the dock to add.
     * @param settings settings.
     * @param identifier identifier.
     */
    void addDock(Widgets::Docks::DockBaseProperties *dock,
                 const QVariantHash &settings = QVariantHash(),
                 const QString &identifier = QString());
    /**
     * @brief Add a dock
     * @param dock the dock to add.
     */
    void addDock(Widgets::Docks::DockProperties *dock);
    /**
     * @brief Remove a dock
     * @param dock the dock to remove.
     */
    void removeDock(Widgets::Docks::DockProperties *dock);
Q_SIGNALS:
    /**
     * @short Count changed
     */
    void countChanged(int count);
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    DockModel(DockModelPrivate *dd, QObject *parent = 0);
    /**
     * @brief Reimplementation of event
     *
     * This reimplementation is done to enable a
     * queued save.
     *
     * @param event event to react to.
     * @return if the event succeeded.
     */
    virtual bool event(QEvent *event);
    /**
     * @short D-pointer
     */
    const QScopedPointer<DockModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(DockModel)
    Q_PRIVATE_SLOT(d_func(), void refreshProvider())
};

}

}

#endif // WIDGETS_DOCKS_DOCKMODEL_H
