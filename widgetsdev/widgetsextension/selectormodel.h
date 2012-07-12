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
 * @file selectormodel.h
 * @short Definition of Widgets::SelectorModel
 *
 * This file contains the definition of the
 * Widgets::SelectorModel class.
 */


#ifndef WIDGETS_SELECTORMODEL_H
#define WIDGETS_SELECTORMODEL_H

#include <QtCore/QAbstractListModel>

namespace Widgets
{

/**
 * @short Model for generic selector page
 *
 * This class is a base class for generic
 * selector page, that provides a lot of
 * clickable entries.
 *
 * Each item of this model contains the
 * information to represent an entry. 
 * It works best with the QML 
 * ClickableEntry element.
 *
 * Modifying this model can be done using
 * - addEntry()
 *
 * This method appends a new entry at
 * the end of the model. In order to 
 * construct a full model, this method
 * can be called when the component is
 * completed, using Component.onCompleted.
 */
class SelectorModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Number of rows in the model
     *
     * This property is mainly used in QML context
     * and is used by the views to track the number
     * of elements in the model.
     *
     * This property is nearly equivalent to
     * rowCount().
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /**
     * @short Model roles
     */
    enum SelectorRole {
        /**
         * @short Identifier role
         */
        IdentifierRole = Qt::UserRole + 1,
        /**
         * @short Text role
         */
        TextRole,
        /**
         * @short Sub-text role
         */
        SubTextRole,
        /**
         * @short Icon role
         */
        IconRole,
        /**
         * @short Indicator icon role
         */
        IndicatorIconRole
    };
    /**
     * @short Default constructor
     *
     * @param parent parent object.
     */
    explicit SelectorModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~SelectorModel();
    /**
     * @short Reimplementation of rowCount
     *
     * This method is the reimplementation of
     * QAbstractListModel::rowCount(). It
     * simply returns the number of rows in this model.
     *
     * @param parent parent model index.
     * @return the number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Number of rows in this model
     *
     * This method is used to retrieve the number
     * of rows in this model.
     *
     * @return number of rows in this model.
     */
    int count() const;
    /**
     * @short Reimplementation of data
     *
     * This method is the reimplementation of
     * QAbstractListModel::data(). It is used
     * by views to retrieve the different
     * roles of the model, based on the row.
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
Q_SIGNALS:
    /**
     * @short Count changed
     *
     * Notify that the row count
     * has changed.
     *
     * @param count value of the new row count.
     */
    void countChanged(int count);
public Q_SLOTS:
    /**
     * @short Add entry 
     * 
     * Adds an entry in the model. An entry must have an
     * identifier in order to be identified. It can have
     * a text, a sub-text, an icon, as well as an indicator
     * icon. This indicator icon is often an icon from the
     * theme, that is used to indicate if the entry is a
     * combobox, or a navigation button etc.
     * 
     * @param identifier an identifier that can be used to identify this entry.
     * @param text the text of this entry.
     * @param subText the sub-text of this entry.
     * @param icon the icon of this entry.
     * @param indicatorIcon the indicator icon of this entry.
     */
    void addEntry(const QVariant &identifier, const QString &text,
                  const QString &subText = QString(),
                  const QString &icon = QString(),
                  const QString &indicatorIcon = QString());
private:
    class SelectorModelPrivate;
    /**
     * @short D-pointer
     */
    SelectorModelPrivate * const d;
};

}

#endif // WIDGETS_SELECTORMODEL_H
