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
 * @file widgetspagemodel.cpp
 * @short Implementation of Widgets::WidgetsPageModel
 */

#include "widgetspagemodel.h"

#include "abstractsettings_p.h"
#include "gridmanager.h"
#include "widgetproviderbase.h"
#include "widgetproperties_p.h"
#include "settings.h"

#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtCore/qmath.h>
#include <QtCore/QStringList>
#include <QtCore/QSize>
#include <QtCore/QRect>

#include <QtDeclarative/QDeclarativeContext>

namespace Widgets
{

/**
 * @brief WIDGET_ELEMENT
 *
 * Used in Widgets::WidgetsPageModel.
 */
static const char *WIDGET_ELEMENT = "widget";


bool widgetsByZLessThan(WidgetProperties *widget1, WidgetProperties *widget2)
{
    return (widget1->z() < widget2->z());
}


/**
 * @internal
 * @short Private class for Widgets::WidgetsPageModelPrivate
 */
class WidgetsPageModelPrivate: public AbstractSettings
{
public:
    /**
     * @internal
     * @short Default constructor
     * @param q Q-pointer.
     */
    WidgetsPageModelPrivate(WidgetsPageModel *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~WidgetsPageModelPrivate();
    /**
     * @internal
     * @brief Clear
     */
    virtual void clear();
    /**
     * @internal
     * @brief Load from XML element
     *
     * @param element the source XML element.
     * @return if the loading succeded.
     */
    virtual bool fromXmlElement(const QDomElement &element);
    /**
     * @internal
     * @brief Save to XML element
     *
     * @param tagName the tag that will be used to create this element.
     * @param document a pointer to the document that is used to create elements.
     * @return the class as an XML element.
     */
    virtual QDomElement toXmlElement(const QString &tagName, QDomDocument *document) const;
    /**
     * @internal
     * @brief Compute a rectangle that is available in the grid
     *
     * This method computes a rectangle that is fit to the provided
     * size. It takes the size of the grid in account, and the other
     * widgets, in order not to have any overlap.
     *
     * If no space was found, an invalid geometry will be returned.
     *
     * @param gridManager grid manager used to perform the operation.
     * @param width width of the widget.
     * @param height height of the widget.
     * @return
     */
    QRect availableRect(Widgets::GridManager *gridManager, int width, int height) const;
    void requestSaveWithUpdatedZ();
    /**
     * @internal
     * @short Page index
     */
    int pageIndex;
    /**
     * @internal
     * @short Data
     */
    QList<WidgetProperties *> data;
    /**
     * @internal
     * @short Provider
     */
    WidgetProviderBase *provider;
private:
    /**
     * @internal
     * @short Q-pointer
     */
    WidgetsPageModel * const q_ptr;
    Q_DECLARE_PUBLIC(WidgetsPageModel)
};

WidgetsPageModelPrivate::WidgetsPageModelPrivate(WidgetsPageModel *q):
    AbstractSettings(q), q_ptr(q)
{
    pageIndex = -1;
    provider = 0;
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

    WidgetPropertiesComponentBuilder *builder = new WidgetPropertiesComponentBuilder();
    BuildManager<WidgetProperties *> *buildManager = new BuildManager<WidgetProperties *>();
    buildManager->setBuilder(builder);


    QDomElement widgetElement = element.firstChildElement(WIDGET_ELEMENT);
    while (!widgetElement.isNull()) {
        builder->setProperties(widgetElement, q);
        WidgetBaseProperties *base = provider->widget(builder->fileName(),
                                                      builder->disambiguation());
        if (base) {
            builder->setWidgetBaseProperties(base);
            buildManager->build();
            q->addWidget(buildManager->element());
            base->deleteLater();
        }

        widgetElement = widgetElement.nextSiblingElement(WIDGET_ELEMENT);
    }

    delete builder;
    delete buildManager;

    return true;
}

QDomElement WidgetsPageModelPrivate::toXmlElement(const QString &tagName,
                                                  QDomDocument *document) const
{
    QDomElement element = document->createElement(tagName);

    WidgetPropertiesXmlBuilder *builder = new WidgetPropertiesXmlBuilder();
    BuildManager<QDomElement> *buildManager = new BuildManager<QDomElement>();
    buildManager->setBuilder(builder);

    foreach(WidgetProperties *widget, data) {
        builder->setProperties(widget, WIDGET_ELEMENT, document);
        buildManager->build();
        element.appendChild(buildManager->element());
    }

    delete builder;
    delete buildManager;
    return element;
}

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

void WidgetsPageModelPrivate::requestSaveWithUpdatedZ()
{
    Q_Q(WidgetsPageModel);

    if (data.isEmpty()) {
        return;
    }

    // Detect the sender if there is one
    // If the sender is a widget, then it
    // should be set to the top z
    // If not, then the last widget is set
    // to the top z
    WidgetProperties *widget = qobject_cast<WidgetProperties *>(q->sender());

    if (!widget) {
        widget = data.last();
    }

    widget->setZ(data.size());
    QList<WidgetProperties *> sortedData = data;
    qStableSort(sortedData.begin(), sortedData.end(), widgetsByZLessThan);

    for (int i = 0; i < sortedData.count(); i++) {
        sortedData[i]->setZ(i);
    }

    requestSave();
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

void WidgetsPageModel::setProvider(WidgetProviderBase *provider)
{
    Q_D(WidgetsPageModel);
    d->provider = provider;
    load();
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
    if (!d->provider) {
        return;
    }

    if (!d->provider->isAvailable()) {
        return;
    }

    if (d->pageIndex < 0) {
        return;
    }

    d->load();
}

void WidgetsPageModel::setEnabled(bool enabled)
{
    Q_D(WidgetsPageModel);
    foreach (WidgetProperties *widget, d->data) {
        widget->setEnabled(enabled);
    }
}

bool WidgetsPageModel::addWidget(WidgetBaseProperties *widget,
                                 Widgets::GridManager *gridManager,
                                 const QVariantMap &settings,
                                 const QString &identifier)
{
    Q_D(WidgetsPageModel);

    if(!widget) {
        return false;
    }

    QRect geometry = d->availableRect(gridManager, widget->minimumWidth(), widget->minimumHeight());
    if (!geometry.isValid()) {
        return false;
    }

    return addWidget(widget, geometry.x(), geometry.y(), 0,
                     geometry.width(), geometry.height(), settings, identifier);
}

bool WidgetsPageModel::addWidget(WidgetBaseProperties *widget,
                                 int x, int y, int z,
                                 int width, int height,
                                 const QVariantMap &settings,
                                 const QString &identifier)
{
    Widgets::WidgetProperties *newWidget;
    if (identifier.isEmpty()) {
        newWidget = new WidgetProperties(widget, x, y, z, width, height, settings, this);
    } else {
        newWidget = new WidgetProperties(widget, identifier,
                                         x, y, z, width, height, settings, this);
    }

    return addWidget(newWidget);
}

bool WidgetsPageModel::addWidget(WidgetProperties *widget)
{
    Q_D(WidgetsPageModel);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    d->data.append(widget);

    emit countChanged();
    endInsertRows();

    d->requestSaveWithUpdatedZ();

    connect(widget, SIGNAL(xChanged()), this, SLOT(requestSaveWithUpdatedZ()));
    connect(widget, SIGNAL(yChanged()), this, SLOT(requestSaveWithUpdatedZ()));
    connect(widget, SIGNAL(widthChanged()), this, SLOT(requestSave()));
    connect(widget, SIGNAL(heightChanged()), this, SLOT(requestSave()));
    connect(widget, SIGNAL(settingsChanged()), this, SLOT(requestSave()));
    return true;
}

bool WidgetsPageModel::removeWidget(WidgetProperties *widget)
{
    Q_D(WidgetsPageModel);

    // Check if the widget is present
    int widgetIndex = d->data.indexOf(widget);
    if (widgetIndex == -1) {
        return false;
    }

    beginRemoveRows(QModelIndex(), widgetIndex, widgetIndex);

    d->data.takeAt(widgetIndex)->deleteLater();

    emit countChanged();
    endRemoveRows();

    d->requestSaveWithUpdatedZ();

    return true;
}

void WidgetsPageModel::clearWidgets()
{
    Q_D(WidgetsPageModel);
    d->clear();
    emit countChanged();

    d->requestSave();
}

//void WidgetsPageModel::relayout(GridManager *gridManager)
//{
//    Q_UNUSED(gridManager)
//}



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

#include "moc_widgetspagemodel.cpp"
