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

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

/**
 * @internal
 * @file qmltree_p.cpp
 * @short Implementation of Widgets::QmlTree
 */

#include "qmltree_p.h"

#include <QtCore/QFile>
#include <QtCore/QVariantMap>

namespace Widgets
{

/**
 * @internal
 * @brief Private class for Widgets::QmlTree
 */
class QmlTreePrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    QmlTreePrivate();
    /**
     * @internal
     * @brief Destructor
     */
    ~QmlTreePrivate();
    /**
     * @internal
     * @brief Index of the closing bracket }
     *
     * This method is used to get the closing bracket
     * that match the opening bracket.
     *
     * @param data data as a string.
     * @param openingIndex opening bracket index.
     * @return index of the closing bracket.
     */
    static int closingBracket(const QString &data, int openingIndex);
    /**
     * @internal
     * @brief Load and clean file
     *
     * This method is used to load and clean a
     * QML file, removing comments and cleaning
     * line breaks.
     *
     * @param file file to read.
     * @return cleaned data.
     */
    static QString cleanedFile(QFile *file);
    /**
     * @internal
     * @brief From QML
     *
     * This method is used to create a node from QML.
     * It do not take the imports in account.
     *
     * @param data data as a string describing the component.
     * @param extractChildren extract children.
     * @return QML tree containing the structure of the data.
     */
    static QmlTree * fromQml(const QString &data, bool extractChildren = false);
    /**
     * @internal
     * @brief Properties
     */
    QMap<QString, QString> properties;
    /**
     * @internal
     * @brief Children
     */
    QList<QmlTree *> children;
    /**
     * @internal
     * @brief Parent
     */
    QmlTree * parent;
    /**
     * @internal
     * @brief Name
     */
    QString name;
    /**
     * @internal
     * @brief Imports
     */
    QStringList imports;
};

QmlTreePrivate::QmlTreePrivate()
{
    parent = 0;
}

QmlTreePrivate::~QmlTreePrivate()
{
    while (!children.isEmpty()) {
        delete children.takeFirst();
    }
}

int QmlTreePrivate::closingBracket(const QString &data, int openingIndex)
{
    if (openingIndex < 0 || openingIndex >= data.size()) {
        return -1;
    }

    int counter = 0;
    int nextIndex = openingIndex + 1;
    int nextOpening = -1;
    int nextClosing = -1;
    do {
        nextOpening = data.indexOf("{", nextIndex);
        nextClosing = data.indexOf("}", nextIndex);

        if (nextOpening > 0 && (nextOpening < nextClosing || nextClosing < 0)) {
            counter ++;
            nextIndex = nextOpening + 1;
        } else if (nextClosing > 0 && (nextClosing < nextOpening || nextOpening < 0)){
            counter --;
            nextIndex = nextClosing + 1;
        }

    } while (counter >= 0 || nextClosing == -1);

    return nextClosing;
}

QString QmlTreePrivate::cleanedFile(QFile *file)
{
    QString data;

    // Clean the file
    // - Remove comments
    // - Set nice brackets formatting
    // - Trim indentation
    bool haveBlockComment = false;
    QRegExp commentLineRegExp ("//(.+)");
    QRegExp blockCommentLineStartRexExp ("/\\*.*");
    QRegExp blockCommentLineEndRegExp ("[^*/]*\\*/");
    while (!file->atEnd()) {
        QString line = file->readLine();
        line = line.remove(commentLineRegExp);

        if (line.indexOf(blockCommentLineStartRexExp) != -1) {
            haveBlockComment = true;
            line = line.remove(blockCommentLineStartRexExp);
        }

        if (haveBlockComment) {
            int indexOfBlockCommentLineEnd = line.indexOf(blockCommentLineEndRegExp);
            if (indexOfBlockCommentLineEnd != -1) {
                line = line.right(line.size() - indexOfBlockCommentLineEnd);
                line = line.remove(blockCommentLineEndRegExp);

                haveBlockComment = false;
            } else {
                line = "";
            }
        }

        line = line.trimmed();
        if (!line.isEmpty()) {
            if (!line.endsWith("{") && !line.endsWith("}")) {
                line.append(";");
            }

            data.append(line);
        }
    }
    data = data.replace(QRegExp("(;\\s+)+"), ";");
    data = data.replace(QRegExp(";\\}"), "}");
    data = data.replace(QRegExp("\\}"), "}");


    // Remove functions
    QRegExp functionRegExp ("function");
    bool valid = true;
    int functionIndex = data.indexOf(functionRegExp);
    while (functionIndex != -1 && valid) {
        int nextBracket = data.indexOf("{", functionIndex);
        int nextClosingBracket = QmlTreePrivate::closingBracket(data, nextBracket);
        if (nextClosingBracket != -1) {
            data = data.remove(functionIndex, nextClosingBracket - functionIndex + 1);
        } else {
            valid = false;
        }
        functionIndex = data.indexOf(functionRegExp);
    }

    if (!valid) {
        return QString();
    }


    // Remove properties
    QRegExp propertyRegExp ("property[^;\\}]+(;|\\})");
    data = data.remove(propertyRegExp);

    // Remove signal handlers
    QRegExp bracketSignalHandlerRegExp(";([^;\\.]+\\.)?on[A-Z0-9_][^\\:]*\\:[^\\{]\\{");
    int signalIndex = data.indexOf(bracketSignalHandlerRegExp);

    valid = true;
    while (signalIndex != -1 && valid) {
        int openBracketIndex = data.indexOf("{", signalIndex);
        int closeBracketIndex = QmlTreePrivate::closingBracket(data, openBracketIndex);
        if (closeBracketIndex != -1) {
            data = data.remove(signalIndex + 1, closeBracketIndex - signalIndex);
        } else {
            valid = false;
        }

        signalIndex = data.indexOf(bracketSignalHandlerRegExp);
    }

    if (!valid) {
        return QString();
    }
    QRegExp simpleSignalHandlerRegExp ("(;([^;\\.]+\\.)?on[A-Z0-9_])[^\\:]*\\:[^;\\}]*");
    data = data.remove(simpleSignalHandlerRegExp);

    return data;
}

QmlTree * QmlTreePrivate::fromQml(const QString &data, bool extractChildren)
{
    QString newData = data;

    // Extract name
    int openBracketIndex = newData.indexOf("{");
    if (openBracketIndex == -1) {
        return 0;
    }

    QString name = newData.left(openBracketIndex).trimmed();

    newData = newData.remove(0, openBracketIndex + 1);
    int closeBracketIndex = newData.lastIndexOf("}");

    newData.truncate(closeBracketIndex);

    // Do a small cleanup, changing anchors {xxx: yyy} anchors.xxx: yyy
    QRegExp anchorsCleanupRegExp("anchors\\s*\\{([^\\}]+)\\}");
    int anchorsCleanupIndex = newData.indexOf(anchorsCleanupRegExp);
    if (anchorsCleanupIndex != -1) {

        QString anchors = anchorsCleanupRegExp.cap(1);
        QStringList anchorsList = anchors.split(QRegExp("\\s*;\\s*"), QString::SkipEmptyParts);

        QStringList newAnchorsList;
        foreach (QString anchor, anchorsList) {
            newAnchorsList.append(QString("anchors.%1").arg(anchor));
        }

        newData.replace(anchorsCleanupRegExp, newAnchorsList.join(";"));
    }

    QList<QmlTree *> children;

    // Extract children
    bool valid = true;
    QRegExp subComponentRegExp ("[^\\;\\{\\}\\:]+\\{");
    int subComponentIndex = newData.indexOf(subComponentRegExp);
    while (subComponentIndex != -1) {
        int openBracketIndex = newData.indexOf("{", subComponentIndex);
        int closeBracketIndex = closingBracket(newData, openBracketIndex);
        if (closeBracketIndex == -1) {
            valid = false;
            break;
        }

        QString component = newData.mid(subComponentIndex,
                                        closeBracketIndex - subComponentIndex + 1);
        // Do extraction here
        if (extractChildren) {
            QmlTree *child = fromQml(component);
            children.append(child);
        }

        newData = newData.remove(subComponentIndex, closeBracketIndex - subComponentIndex + 1);
        subComponentIndex = newData.indexOf(subComponentRegExp);
    }

    if (!valid) {
        return 0;
    }

    QmlTree *tree = new QmlTree();
    tree->setName(name);

    foreach (QmlTree *child, children) {
        tree->addChild(child);
    }

    // Extract properties
    QStringList propertiesString = newData.split(QRegExp("\\s*;\\s*"));
    foreach (QString propertyString, propertiesString) {
        QStringList propertyValues = propertyString.split(":");
        if (propertyValues.count() == 2) {
            tree->addProperty(propertyValues.at(0).trimmed(),
                              propertyValues.at(1).trimmed());
        }
    }

    return tree;
}

////// End of private class //////

QmlTree::QmlTree(QmlTree *parent):
    d_ptr(new QmlTreePrivate())
{
    Q_D(QmlTree);
    d->parent = parent;
}

QmlTree::~QmlTree()
{

}

QmlTree * QmlTree::parent() const
{
    Q_D(const QmlTree);
    return d->parent;
}

void QmlTree::setParent(QmlTree *parent)
{
    Q_D(QmlTree);
    d->parent = parent;
}

QString QmlTree::name() const
{
    Q_D(const QmlTree);
    return d->name;
}

void QmlTree::setName(const QString &name)
{
    Q_D(QmlTree);
    d->name = name;
}

QStringList QmlTree::imports() const
{
    Q_D(const QmlTree);
    return d->imports;
}

void QmlTree::addImport(const QString &import)
{
    Q_D(QmlTree);
    d->imports.append(import);
}

bool QmlTree::hasProperty(const QString &name) const
{
    Q_D(const QmlTree);
    return d->properties.contains(name);
}

QString QmlTree::property(const QString &name) const
{
    Q_D(const QmlTree);
    return d->properties.value(name);
}

void QmlTree::addProperty(const QString &name, const QString &property)
{
    Q_D(QmlTree);
    d->properties.insert(name, property);
}

QList<QmlTree *> QmlTree::children() const
{
    Q_D(const QmlTree);
    return d->children;
}

void QmlTree::addChild(QmlTree *child)
{
    Q_D(QmlTree);
    child->setParent(this);
    d->children.append(child);
}

QmlTree * QmlTree::fromQml(const QString &path, bool extractChildren)
{
    QFile file (path);
    if (!file.open(QIODevice::ReadOnly)) {
        return 0;
    }

    // Cleaned data
    QString data = QmlTreePrivate::cleanedFile(&file);
    if (data.isEmpty()) {
        return 0;
    }

    // Extract the imports
    QRegExp importRegExp ("(import[^;]+);");
    QStringList importList;
    int importSize = 0;

    int index = data.indexOf(importRegExp);
    if (index != 0) {
        return 0;
    }

    while (index != -1) {
        QString import = importRegExp.cap(1);
        importList.append(import);
        importSize += import.size() + 1;

        index = data.indexOf(importRegExp, index + import.size());
    }
    data = data.remove(0, importSize);

    QmlTree *tree = QmlTreePrivate::fromQml(data, extractChildren);
    if (!tree) {
        return 0;
    }

    foreach (QString import, importList) {
        tree->addImport(import);
    }

    return tree;
}

}
