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

#include "widgetspagemodel.h"
#include "widgetproperties.h"

#include "abstractsettings_p.h"
#include "gridmanager.h"
#include "settings.h"
#include "packagemanager.h"

#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtCore/qmath.h>
#include <QtCore/QStringList>
#include <QtCore/QSize>
#include <QtCore/QRect>

#include <QtDeclarative/QDeclarativeContext>

namespace Widgets
{

static const char *WIDGET_ELEMENT = "widget";

/**
 * @internal
 * @short Private class for DisplayedPageWidgetsModel
 */
class WidgetsPageModelPrivate: public AbstractSettingsPrivate
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
    WidgetsPageModelPrivate(WidgetsPageModel *q);
    virtual ~WidgetsPageModelPrivate();
    virtual void clear();
    virtual bool fromXmlElement(const QDomElement &element);
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    /**
     * @short Load settings
     *
     * This method is used to retrieve
     * the saved widgets and create them.
     */
//    void loadSettings();
    QRect availableRect(Widgets::GridManager *gridManager, int width, int height) const;
    /**
     * @short Index of this page
     */
    int pageIndex;
    /**
     * @short A list of WidgetProperties
     *
     * This list of WidgetProperties is the
     * internal storage of the model.
     */
    QList<WidgetProperties *> data;
    /**
     * @short A list of WidgetProperties sorted by Z
     *
     * This list of WidgetProperties is used to
     * manage z coordinate of the widgets.
     */
//    QList<WidgetProperties *> widgetsByZ;
    /**
     * @short A map associating identifier to widgets
     *
     * This map associates the identifier of a widget
     * to the WidgetProperties that corresponds.
     */
//    QMap<QString, WidgetProperties *> widgetsByIdentifier;
    /**
     * @short Identifiers
     *
     * This list of identifiers is used to
     * track the widgets that were added.
     *
     * This list is used in settings.
     */
//    QStringList identifiers;
    /**
     * @short %Settings
     */
//    Settings * const settings;
    /**
     * @short Package manager
     */
    PackageManager *packageManager;
private:
    /**
     * @short Q-pointer
     */
    WidgetsPageModel * const q_ptr;
    Q_DECLARE_PUBLIC(WidgetsPageModel)
};

WidgetsPageModelPrivate::WidgetsPageModelPrivate(WidgetsPageModel *q):
    AbstractSettingsPrivate(q), q_ptr(q)
{
    pageIndex = -1;
    packageManager = 0;
}

WidgetsPageModelPrivate::~WidgetsPageModelPrivate()
{
    clear();
}

void WidgetsPageModelPrivate::clear()
{
    Q_Q(WidgetsPageModel);
    q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
    while (!data.isEmpty()) {
        delete data.takeFirst();
    }
    q->endRemoveRows();
}

bool WidgetsPageModelPrivate::fromXmlElement(const QDomElement &element)
{
    Q_Q(WidgetsPageModel);
    if (element.tagName() != SETTINGS_ELEMENT) {
        return false;
    }

    QDomElement widgetElement = element.firstChildElement(WIDGET_ELEMENT);
    while (!widgetElement.isNull()) {
        WidgetProperties *incompleteWidget = new WidgetProperties(q);
        if (incompleteWidget->fromXmlElement(widgetElement)) {
            WidgetBaseProperties *widgetBase =
                    packageManager->widget(incompleteWidget->packageIdentifier(),
                                           incompleteWidget->fileName());
            if (widgetBase != 0) {
                QRect geometry = QRect(incompleteWidget->x(), incompleteWidget->y(),
                                       incompleteWidget->width(), incompleteWidget->height());
                int z = incompleteWidget->z();

                q->addWidget(widgetBase, geometry, z,
                             incompleteWidget->settings(),
                             incompleteWidget->identifier());
                widgetBase->deleteLater();
            }
        }
        incompleteWidget->deleteLater();
        widgetElement = widgetElement.nextSiblingElement(WIDGET_ELEMENT);
    }

    return true;
}

QDomElement WidgetsPageModelPrivate::toXmlElement(const QString &tagName,
                                                  QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);

    foreach(WidgetProperties *widget, data) {
        element.appendChild(widget->toXmlElement(WIDGET_ELEMENT, document));
    }
    return element;
}

//void WidgetsPageModelPrivate::loadSettings()
//{
    /*
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

    }*/

//}

QRect WidgetsPageModelPrivate::availableRect(GridManager *gridManager, int width, int height) const
{
    int cellWidth = gridManager->gridCellWidth();
    int cellHeight = gridManager->gridCellWidth();
    int cellHMargin = gridManager->gridCellHorizontalMargin();
    int cellVMargin = gridManager->gridCellVerticalMargin();

    QList<QRect> widgetsRects;

    foreach (WidgetProperties * widget, data) {
        QRect widgetRect = QRect(widget->x(), widget->y(), widget->width(), widget->height());
        widgetsRects.append(widgetRect);
    }

    int x = 0;
    int y = 0;
    bool found = false;
    QSize correctSize = gridManager->fitSize(QSize(width, height));
    int removedWidth = qCeil((float) correctSize.width()
                             / ((float) cellWidth + (float) cellHMargin)) - 1;
    int removedHeight = qCeil((float) correctSize.height()
                             / ((float) cellHeight + (float) cellVMargin)) - 1;

    QSize removedSize = QSize(removedWidth ,removedHeight);

    QRect widgetRect = QRect(QPoint(x, y), correctSize);
    while (y < (gridManager->gridHeight() - removedSize.height()) && !found) {
        widgetRect.setY(y * (cellHeight + cellVMargin));
        widgetRect.setHeight(correctSize.height());
        while (x < gridManager->gridWidth() - removedSize.width() && !found) {
            bool intersects = false;
            widgetRect.setX(x * (cellWidth + cellHMargin));
            widgetRect.setWidth(correctSize.width());

            foreach(QRect otherRect, widgetsRects) {
                if (widgetRect.intersects(otherRect)) {
                    intersects = true;
                }
            }

            if (!intersects) {
                found = true;
            }
            x++;
        }
        x = 0;
        y++;
    }

    widgetRect.setTopLeft(gridManager->fitPosition(widgetRect.topLeft()));
    if (found) {
        return widgetRect;
    } else {
        return QRect();
    }
}

////// End of private class //////

WidgetsPageModel::WidgetsPageModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new WidgetsPageModelPrivate(this))
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(WidgetRole, "widget");
    setRoleNames(roles);
}

WidgetsPageModel::WidgetsPageModel(WidgetsPageModelPrivate *dd, QObject *parent):
    QAbstractListModel(parent),
    d_ptr(dd)
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(WidgetRole, "widget");
    setRoleNames(roles);
}

WidgetsPageModel::~WidgetsPageModel()
{
}

int WidgetsPageModel::pageIndex() const
{
    Q_D(const WidgetsPageModel);
    return d->pageIndex;
}

int WidgetsPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const WidgetsPageModel);
    return d->data.count();
}

int WidgetsPageModel::count() const
{
    return rowCount();
}

PackageManager * WidgetsPageModel::packageManager() const
{
    Q_D(const WidgetsPageModel);
    return d->packageManager;
}

QVariant WidgetsPageModel::data(const QModelIndex &index, int role) const
{
    Q_D(const WidgetsPageModel);
    if (index.row() < 0 or index.row() > rowCount()) {
        return QVariant();
    }

    switch(role) {
    case WidgetRole:
        return QVariant::fromValue(d->data.at(index.row()));
        break;
    default:
        return QVariant();
        break;
    }
}

void WidgetsPageModel::setPageIndex(int index)
{
    Q_D(WidgetsPageModel);
    if (d->pageIndex != index) {
        d->pageIndex = index;

        d->componentName = QString("widget-%1").arg(index);
        load();

        emit pageIndexChanged();
    }
}

void WidgetsPageModel::load()
{
    Q_D(WidgetsPageModel);
    if (d->packageManager == 0) {
        return;
    }

    if (d->pageIndex < 0) {
        return;
    }

    d->load();
}

bool WidgetsPageModel::addWidget(WidgetBaseProperties *widget,
                                 Widgets::GridManager *gridManager,
                                 const QVariantMap &settings,
                                 const QString &identifier)
{
    Q_D(WidgetsPageModel);

    if(widget == 0) {
        return false;
    }

    QRect geometry = d->availableRect(gridManager, widget->minimumWidth(), widget->minimumHeight());
    if (!geometry.isValid()) {
        return false;
    }

    return addWidget(widget, geometry, 0, settings, identifier);
}

bool WidgetsPageModel::addWidget(WidgetBaseProperties *widget,
                                 const QRect &geometry, int z,
                                 const QVariantMap &settings,
                                 const QString &identifier)
{
    Q_D(WidgetsPageModel);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    WidgetProperties *newWidget;
    if (identifier.isEmpty()) {
        newWidget = new WidgetProperties(widget, geometry, z, settings, this);
    } else {
        newWidget = new WidgetProperties(widget, geometry, z, identifier, settings, this);
    }

    d->data.append(newWidget);

    emit countChanged(rowCount());
    endInsertRows();

    d->requestSave();
    return true;
}

void WidgetsPageModel::setPackageManager(PackageManager *packageManager)
{
    Q_D(WidgetsPageModel);
    if (d->packageManager != packageManager) {
        d->packageManager = packageManager;
        emit packageManagerChanged();
    }

    if (d->packageManager != 0) {
        load();
    }
}

void WidgetsPageModel::relayout(GridManager *gridManager)
{

}



//int WidgetsViewPageModel::pageIndex() const
//{
//    return d->pageIndex;
//}

//WidgetProperties * WidgetsViewPageModel::widget(int index) const
//{
//    if (index < 0 || index >= rowCount()) {
//        return 0;
//    }
//    return d->widgets.at(index);
//}

//void WidgetsViewPageModel::addWidget(WidgetBaseProperties *widget,
//                                     int x, int y,
//                                     int width, int height,
//                                     const QVariantMap &settings,
//                                     const QString &identifier, int z)
//{
//    if(widget == 0) {
//        return;
//    }

//    beginInsertRows(QModelIndex(), rowCount(), rowCount());

//    // The last added Z is either the highest
//    // (if the passed z is -1) or the passed
//    // z (if it is not -1)
//    int trueZ = rowCount();
//    if (z != -1) {
//        trueZ = z;
//    }

//    // Create a new widget by either using the passed identifier
//    // either by generating a new one
//    WidgetProperties *newWidget;
//    if (identifier.isEmpty()) {
//        newWidget = new WidgetProperties(widget->name(),
//                                         widget->defaultWidth(), widget->defaultHeight(),
//                                         widget->qmlFile(), widget->package(),
//                                         widget->hasSettings(),
//                                         x, y, trueZ, width, height,
//                                         settings, this);
//    } else {
//        newWidget = new WidgetProperties(widget->name(),
//                                         widget->defaultWidth(), widget->defaultHeight(),
//                                         widget->qmlFile(), widget->package(),
//                                         widget->hasSettings(),
//                                         identifier,
//                                         x, y, trueZ, width, height,
//                                         settings, this);
//    }

//    // Append the widget to the list
//    d->widgets.append(newWidget);

//    // Append it to the list by Z
//    // since it is the maximum
////    d->widgetsByZ.append(newWidget);

//    // Add it to the map between
//    // widget and identifier
//    d->widgetsByIdentifier.insert(newWidget->identifier(), newWidget);

//    emit countChanged(rowCount());
//    endInsertRows();

//    // Save settings
//    // Add the new widget to the list of identifiers
//    d->identifiers.append(newWidget->identifier());
//    QString key = QString("page%1/identifiers").arg(d->pageIndex);
//    d->settings->setValue(key, d->identifiers);

//    // Save the widget as a map
//    key = QString("page%1/widget_%2").arg(d->pageIndex).arg(newWidget->identifier());
//    d->settings->setValue(key, newWidget->toMap());
//}

//void WidgetsViewPageModel::removeWidget(WidgetProperties *widget)
//{
//    // Check if the widget is present
//    int widgetIndex = d->widgets.indexOf(widget);
//    if (widgetIndex == -1) {
//        return;
//    }

//    beginRemoveRows(QModelIndex(), widgetIndex, widgetIndex);

//    // Remove the widget out of the list
//    d->widgets.removeAt(widgetIndex);

//    // Remove also the widget from the list by Z
////    d->widgetsByZ.removeAt(widgetToDelete->z());

//    // Remove the widget from the map between
//    // widget and identifier
//    d->widgetsByIdentifier.remove(widget->identifier());

//    // Need to update all widgets after the removed one
//    // because their z are no longer valid
////    int deletedZ = widgetToDelete->z();
////    for(int z = deletedZ; z < rowCount(); z++) {
////        d->widgetsByZ.at(z)->setZ(z);
////    }

//    // Data changed in the whole model after the Z updates
////    emit dataChanged(this->index(0), this->index(rowCount() - 1));

//    emit countChanged(rowCount());
//    endRemoveRows();

//    // Save settings
//    // Remove the widget from the list of identifiers
//    d->identifiers.removeAll(widget->identifier());
//    QString key = QString("page%1/identifiers").arg(d->pageIndex);
//    d->settings->setValue(key, d->identifiers);

//    // Remove the widget settings
//    key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
//    d->settings->remove(key);

//    // Delete the widget
//    widget->deleteLater();

//    // Update the settings of the others widgets
////    for(int z = deletedZ; z < rowCount(); z++) {
////        WidgetProperties * widget = d->widgetsByZ.at(z);

////        key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
////        d->settings->setValue(key, widget->toMap());
////    }
//}

//void WidgetsViewPageModel::updateWidget(const QString &identifier, int x, int y,
//                                        int width, int height)
//{
//    // Get the widget
//    WidgetProperties *widget = d->widgetsByIdentifier.value(identifier);

//    // Check the widget
//    if(widget == 0) {
//        return;
//    }

//    int widgetIndex = d->widgets.indexOf(widget);
//    if (widgetIndex == -1) {
//        return;
//    }

//    // Update it
//    widget->setX(x);
//    widget->setY(y);
//    widget->setWidth(width);
//    widget->setHeight(height);

//    // Update it's z coordinate
////    int initialZ = widget->z();
////    d->widgetsByZ.takeAt(initialZ);
////    for(int z = initialZ; z < rowCount() - 1; z++) {
////        d->widgetsByZ.at(z)->setZ(z);
////    }
////    d->widgetsByZ.append(widget);
////    widget->setZ(rowCount() - 1);

//    // Data changed in the whole model after the Z updates
////    emit dataChanged(this->index(0), this->index(rowCount() - 1));
//    emit dataChanged(this->index(widgetIndex), this->index(widgetIndex));
//    QString key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
//    d->settings->setValue(key, widget->toMap());


//    // Update the settings of all the widgets from initialZ
////    for(int z = initialZ; z < rowCount(); z++) {
////        WidgetProperties * widget = d->widgetsByZ.at(z);

////        QString key = QString("page%1/widget_%2").arg(d->pageIndex).arg(widget->identifier());
////        d->settings->setValue(key, widget->toMap());
////    }
//}

bool WidgetsPageModel::event(QEvent *event)
{
    Q_D(WidgetsPageModel);
    if (event->type() == QEvent::UpdateRequest) {
        d->save();
        return true;
    }
    return QObject::event(event);
}

}
