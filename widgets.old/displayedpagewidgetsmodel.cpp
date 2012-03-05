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
 * @file displayedpagewidgetsmodel.cpp
 * @short Implementation of Widgets::DisplayedPageWidgetsModel
 *
 * This file contains the implemetation of the
 * Widgets::DisplayedPageWidgetsModel class and the declaration and
 * implementation of Widgets::DisplayedPageWidgetsModel::DisplayedPageWidgetsModelPrivate.
 */

#include "displayedpagewidgetsmodel.h"
#include "widgetproperties.h"
#include "settings.h"
#include "packagemanager.h"

#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QSize>
#include <QtCore/QRect>

namespace Widgets
{

/**
 * @internal
 * @short Private class for DisplayedPageWidgetsModel
 */
class DisplayedPageWidgetsModel::DisplayedPageWidgetsModelPrivate
{
public:
    /**
     * @short Default constructor
     *
     * @param pageIndex index of this page.
     * @param settings Settings object used to manage settings.
     * @param packageManager PackageManager object used to provide available widgets.
     * @param parent parent Q-pointer.
     */
    DisplayedPageWidgetsModelPrivate(int pageIndex, Settings *settings,
                                     PackageManager *packageManager,
                                     DisplayedPageWidgetsModel *parent);
    /**
     * @short Destructor
     */
    ~DisplayedPageWidgetsModelPrivate();
    /**
     * @short Load settings
     *
     * This method is used to retrieve
     * the saved widgets and create them.
     */
    void loadSettings();
    /**
     * @short Index of this page
     */
    const int pageIndex;
    /**
     * @short A list of WidgetProperties
     *
     * This list of WidgetProperties is the
     * internal storage of the model.
     */
    QList<WidgetProperties *> widgets;
    /**
     * @short A list of WidgetProperties sorted by Z
     *
     * This list of WidgetProperties is used to
     * manage z coordinate of the widgets.
     */
    QList<WidgetProperties *> widgetsByZ;
    /**
     * @short A map associating identifier to widgets
     *
     * This map associates the identifier of a widget
     * to the WidgetProperties that corresponds.
     */
    QMap<QString, WidgetProperties *> widgetsByIdentifier;
    /**
     * @short Identifiers
     *
     * This list of identifiers is used to
     * track the widgets that were added.
     *
     * This list is used in settings.
     */
    QStringList identifiers;
    /**
     * @short %Settings
     */
    Settings * const settings;
    /**
     * @short Package manager
     */
    PackageManager * const packageManager;
    /**
     * @short Q-pointer
     */
    DisplayedPageWidgetsModel * const q;
};

DisplayedPageWidgetsModel::DisplayedPageWidgetsModelPrivate::
                           DisplayedPageWidgetsModelPrivate(int pageIndex,
                                                            Settings *settings,
                                                            PackageManager *packageManager,
                                                            DisplayedPageWidgetsModel * parent):
    pageIndex(pageIndex), settings(settings), packageManager(packageManager), q(parent)
{
}

DisplayedPageWidgetsModel::DisplayedPageWidgetsModelPrivate::~DisplayedPageWidgetsModelPrivate()
{
    // Delete allocated items
    while (!widgets.isEmpty()) {
        widgets.takeFirst()->deleteLater();
    }
}

void DisplayedPageWidgetsModel::DisplayedPageWidgetsModelPrivate::loadSettings()
{
    if(settings == 0 || packageManager == 0) {
        return;
    }

    // Key and identifiers
    QString key = QString("page%1/identifiers").arg(pageIndex);
    QStringList identifiers = settings->value(key).toStringList();

    // Retrieve all widgets
    foreach (QString identifier, identifiers) {

        // Key to the widget
        QString key = QString("page%1/widget_%2").arg(pageIndex).arg(identifier);
        QVariantMap widgetMap = settings->value(key).toMap();

        // Get the widget base properties
        QString qmlFile = widgetMap.value("qmlFile").toString();
        WidgetBaseProperties *widgetBase = packageManager->widget(qmlFile);

        // Construct the widget and add it
        if(widgetBase != 0) {
            QRect rect = widgetMap.value("rect").toRect();
            int z = widgetMap.value("z").toInt();
            QVariantMap settings = widgetMap.value("settings").toMap();
            q->addWidget(widgetBase, rect.x(), rect.y(), rect.width(), rect.height(),
                         settings, identifier, z);
        }

    }

}

////// End of private class //////

DisplayedPageWidgetsModel::DisplayedPageWidgetsModel(int pageIndex, Settings *settings,
                                                     PackageManager *packageManager,
                                                     QObject *parent):
    QAbstractListModel(parent),
    d(new DisplayedPageWidgetsModelPrivate(pageIndex, settings, packageManager, this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(WidgetRole, "widget");
    setRoleNames(roles);

    // load settings
    d->loadSettings();
}

DisplayedPageWidgetsModel::~DisplayedPageWidgetsModel()
{
    delete d;
}

int DisplayedPageWidgetsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return d->widgets.count();
}

int DisplayedPageWidgetsModel::count() const
{
    return rowCount();
}

QVariant DisplayedPageWidgetsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 or index.row() > rowCount()) {
        return QVariant();
    }

    switch(role) {
    case WidgetRole:
        return QVariant::fromValue(d->widgets.at(index.row()));
        break;
    default:
        return QVariant();
        break;
    }
}

int DisplayedPageWidgetsModel::pageIndex() const
{
    return d->pageIndex;
}

WidgetProperties * DisplayedPageWidgetsModel::widget(int index) const
{
    if (index < 0 || index >= rowCount()) {
        return 0;
    }
    return d->widgets.at(index);
}

void DisplayedPageWidgetsModel::addWidget(WidgetBaseProperties *widget,
                                     int x, int y,
                                     int width, int height,
                                     const QVariantMap &settings,
                                     const QString &identifier, int z)
{
    if(widget == 0) {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    // The last added Z is either the highest
    // (if the passed z is -1) or the passed
    // z (if it is not -1)
    int trueZ = rowCount();
    if (z != -1) {
        trueZ = z;
    }

    // Create a new widget by either using the passed identifier
    // either by generating a new one
    WidgetProperties *newWidget;
    if (identifier.isEmpty()) {
        newWidget = new WidgetProperties(widget->name(),
                                         widget->defaultWidth(), widget->defaultHeight(),
                                         widget->qmlFile(), widget->package(),
                                         widget->hasSettings(),
                                         x, y, trueZ, width, height,
                                         settings, this);
    } else {
        newWidget = new WidgetProperties(widget->name(),
                                         widget->defaultWidth(), widget->defaultHeight(),
                                         widget->qmlFile(), widget->package(),
                                         widget->hasSettings(),
                                         identifier,
                                         x, y, trueZ, width, height,
                                         settings, this);
    }

    // Append the widget to the list
    d->widgets.append(newWidget);

    // Append it to the list by Z
    // since it is the maximum
//    d->widgetsByZ.append(newWidget);

    // Add it to the map between
    // widget and identifier
    d->widgetsByIdentifier.insert(newWidget->identifier(), newWidget);

    emit countChanged(rowCount());
    endInsertRows();

    // Save settings
    // Add the new widget to the list of identifiers
    d->identifiers.append(newWidget->identifier());
    QString key = QString("page%1/identifiers").arg(d->pageIndex);
    d->settings->setValue(key, d->identifiers);

    // Save the widget as a map
    key = QString("page%1/widget_%2").arg(d->pageIndex).arg(newWidget->identifier());
    d->settings->setValue(key, newWidget->toMap());
}

void DisplayedPageWidgetsModel::removeWidget(WidgetProperties *widget)
{
    // Check if the widget is present
    int widgetIndex = d->widgets.indexOf(widget);
    if (widgetIndex == -1) {
        return;
    }

    beginRemoveRows(QModelIndex(), widgetIndex, widgetIndex);

    // Remove the widget out of the list
    d->widgets.removeAt(widgetIndex);

    // Remove also the widget from the list by Z
//    d->widgetsByZ.removeAt(widgetToDelete->z());

    // Remove the widget from the map between
    // widget and identifier
    d->widgetsByIdentifier.remove(widget->identifier());

    // Need to update all widgets after the removed one
    // because their z are no longer valid
//    int deletedZ = widgetToDelete->z();
//    for(int z = deletedZ; z < rowCount(); z++) {
//        d->widgetsByZ.at(z)->setZ(z);
//    }

    // Data changed in the whole model after the Z updates
//    emit dataChanged(this->index(0), this->index(rowCount() - 1));

    emit countChanged(rowCount());
    endRemoveRows();

    // Save settings
    // Remove the widget from the list of identifiers
    d->identifiers.removeAll(widget->identifier());
    QString key = QString("page%1/identifiers").arg(d->pageIndex);
    d->settings->setValue(key, d->identifiers);

    // Remove the widget settings
    key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
    d->settings->remove(key);

    // Delete the widget
    widget->deleteLater();

    // Update the settings of the others widgets
//    for(int z = deletedZ; z < rowCount(); z++) {
//        WidgetProperties * widget = d->widgetsByZ.at(z);

//        key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
//        d->settings->setValue(key, widget->toMap());
//    }
}

void DisplayedPageWidgetsModel::updateWidget(const QString &identifier, int x, int y,
                                        int width, int height)
{
    // Get the widget
    WidgetProperties *widget = d->widgetsByIdentifier.value(identifier);

    // Check the widget
    if(widget == 0) {
        return;
    }

    int widgetIndex = d->widgets.indexOf(widget);
    if (widgetIndex == -1) {
        return;
    }

    // Update it
    widget->setX(x);
    widget->setY(y);
    widget->setWidth(width);
    widget->setHeight(height);

    // Update it's z coordinate
//    int initialZ = widget->z();
//    d->widgetsByZ.takeAt(initialZ);
//    for(int z = initialZ; z < rowCount() - 1; z++) {
//        d->widgetsByZ.at(z)->setZ(z);
//    }
//    d->widgetsByZ.append(widget);
//    widget->setZ(rowCount() - 1);

    // Data changed in the whole model after the Z updates
//    emit dataChanged(this->index(0), this->index(rowCount() - 1));
    emit dataChanged(this->index(widgetIndex), this->index(widgetIndex));
    QString key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
    d->settings->setValue(key, widget->toMap());


    // Update the settings of all the widgets from initialZ
//    for(int z = initialZ; z < rowCount(); z++) {
//        WidgetProperties * widget = d->widgetsByZ.at(z);

//        QString key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
//        d->settings->setValue(key, widget->toMap());
//    }
}

}
