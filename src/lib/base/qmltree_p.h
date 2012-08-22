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

#ifndef WIDGETS_QMLTREE_H
#define WIDGETS_QMLTREE_H

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file qmltree_p.h
 * @short Definition of Widgets::QmlTree
 */

#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>
#include <QtCore/QtGlobal>

namespace Widgets
{

class QmlTreePrivate;

/**
 * @internal
 * @brief QML tree
 *
 * This class is used to store the structure of a QML file
 * as a tree. This class represents a node of the tree, and
 * children, as well as parent, can be accessed through
 * - parent()
 * - children()
 *
 * The name of the component as well as it's properties are
 * accessed through
 * - name()
 * - property()
 *
 * This class do not extract functions and declared properties.
 */
class QmlTree
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param parent parent node.
     */
    explicit QmlTree(QmlTree *parent = 0);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~QmlTree();
    /**
     * @brief Parent
     * @return parent.
     */
    QmlTree * parent() const;
    /**
     * @brief Set parent
     * @param parent parent.
     */
    void setParent(QmlTree *parent);
    /**
     * @brief Name
     * @return name.
     */
    QString name() const;
    /**
     * @brief Set name
     * @param name name.
     */
    void setName(const QString &name);
    /**
     * @brief Imports
     * @return imports.
     */
    QStringList imports() const;
    /**
     * @brief Add import
     * @param import import.
     */
    void addImport(const QString &import);
    /**
     * @brief Has property
     * @param name name of the property.
     * @return if this node have the property.
     */
    bool hasProperty(const QString &name) const;
    /**
     * @brief Property
     * @param name name of the property.
     * @return property.
     */
    QString property(const QString &name) const;
    /**
     * @brief Add property
     * @param name name of the property.
     * @param property property.
     */
    void addProperty(const QString &name, const QString &property);
    /**
     * @brief Children
     * @return children.
     */
    QList<QmlTree *> children() const;
    /**
     * @brief Add child
     * @param child child.
     */
    void addChild(QmlTree * child);
    /**
     * @brief From QML file
     *
     * This method is used to parse a QML file and extract
     * the structure as a tree. Children can be ignored
     * and only the parent node can be extracted in order
     * to speed up the extraction.
     *
     * @param path path of the QML file.
     * @param extractChildren if the children should be extracted.
     * @return QML tree containing the structure of the file.
     */
    static QmlTree * fromQml(const QString &path, bool extractChildren = false);
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<QmlTreePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(QmlTree)
};

}

#endif // WIDGETS_QMLTREE_H
