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

#ifndef WIDGETS_COMPONENTBASE_H
#define WIDGETS_COMPONENTBASE_H

/**
 * @file componentbase.h
 * @short Definition of Widgets::ComponentBase
 */

#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QScopedPointer>
#include <QtCore/QStringList>

#include "widgets_global.h"

namespace Widgets
{

class ComponentBasePrivate;
/**
 * @brief Base for all components
 *
 * This class is used to represent all the informations that
 * are shared between all components, including packages, widgets
 * and docks. It handles localized contents such as name and
 * description, as well as icons, and can be accessed through QML.
 *
 * Those informations are
 * - icon(), that is an icon for the component.
 * - defaultName(), that is the name that of the component without any translation
 *   (usually in english).
 * - name(), that is the translated name, if available.
 * - defaultDescription(), that is the description, or comment of the component without any
 *   translation (usually in english).
 * - description(), that is the translated description, if available.
 *
 * The page about \ref packageCreationMetaSubsection "desktop file creation" provides more
 * information about how desktop files should be written.
 */
class ComponentBase: public QObject
{
    Q_OBJECT
    /**
     * @short Icon of the component
     */
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    /**
     * @short Default name of the component
     */
    Q_PROPERTY(QString defaultName READ defaultName NOTIFY defaultNameChanged)
    /**
     * @short Name of the component
     *
     * This property hold the translated name of this component, using
     * the system locales. If a translation cannot be found, the default
     * name is used instead.
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    /**
     * @short Default description of the component
     */
    Q_PROPERTY(QString defaultDescription READ defaultDescription NOTIFY defaultDescriptionChanged)
    /**
     * @short Description of the component
     *
     * This property hold the translated description of this component, using
     * the system locales. If a translation cannot be found, the default
     * description is used instead.
     */
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit ComponentBase(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~ComponentBase();
    /**
     * @brief If the component is valid
     *
     * This method is used to check if the component
     * is valid. If the component failed to be created,
     * this method will return false.
     *
     * @return if the component is valid.
     */
    bool isValid() const;
    /**
     * @short Icon of the component
     * @return icon of the component.
     */
    QString icon() const;
    /**
     * @brief Languages
     *
     * This method is used to retrieve the available
     * languages for the current component. This includes
     * languages in which names and or descriptions were
     * translated.
     *
     * @return languages.
     */
    QStringList languages() const;
    /**
     * @brief Default name of the component
     * @return default name of the component.
     */
    QString defaultName() const;
    /**
     * @short Name of the component
     * @return name of the component.
     */
    QString name() const;
    /**
     * @short Name of the component
     *
     * This method is used to retrieve the name of the
     * component in a specific language
     *
     * @param language language of the name.
     * @return name of the component in the given language.
     */
    QString name(const QString &language) const;
    /**
     * @short Default description of the component
     * @return default description of the component.
     */
    QString defaultDescription() const;
    /**
     * @short Description of the component
     * @return description of the component.
     */
    QString description() const;
    /**
     * @short Description of the component
     *
     * This method is used to retrieve the description of the
     * component in a specific language
     *
     * @param language language of the description.
     * @return description of the component in the given language.
     */
    QString description(const QString &language) const;
Q_SIGNALS:
    /**
     * @brief Icon changed
     */
    void iconChanged();
    /**
     * @brief Default name changed
     */
    void defaultNameChanged();
    /**
     * @brief Name changed
     */
    void nameChanged();
    /**
     * @brief Default description changed
     */
    void defaultDescriptionChanged();
    /**
     * @brief Description changed
     */
    void descriptionChanged();
protected:
    /**
     * @brief Constructor for D-pointer
     * @param dd parent D-pointer.
     * @param parent parent object.
     */
    ComponentBase(ComponentBasePrivate *dd, QObject *parent = 0);
    /**
     * @brief Set the icon of the component
     * @param icon icon of the component.
     */
    void setIcon(const QString &icon);
    /**
     * @brief Set the default name of the component
     * @param name default name of the component.
     */
    void setDefaultName(const QString &name);
    /**
     * @brief Add a name
     *
     * This method is used to add a name, associated to
     * a given language, to this component.
     *
     * @param language language of the name.
     * @param name name to add.
     */
    void addName(const QString &language, const QString &name);
    /**
     * @brief Set the default description of the component
     * @param description default description of the component.
     */
    void setDefaultDescription(const QString &description);
    /**
     * @brief Add a description
     *
     * This method is used to add a description, associated to
     * a given language, to this component.
     *
     * @param language language of the description.
     * @param description description to add.
     */
    void addDescription(const QString &language, const QString &description);
    /**
     * @brief Clearn names and descriptions
     *
     * This method is used to clear all names and descriptions
     * of this component. It do not affect default name and
     * description.
     */
    void clearNamesAndDescriptions();
    /**
     * @brief D-pointer
     */
    const QScopedPointer<ComponentBasePrivate> d_pointer;
private:
    W_DECLARE_PRIVATE(ComponentBase)

};

}

#endif // WIDGETS_COMPONENTBASE_H
