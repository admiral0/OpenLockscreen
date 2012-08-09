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

#ifndef WIDGETS_BUILDERPATTERNINTERFACES_P_H
#define WIDGETS_BUILDERPATTERNINTERFACES_P_H

/**
 * @internal
 * @file builderpatterninterfaces_p.h
 * @short Definition of builder pattern interfaces.
 */

// Warning
//
// This file exists for the convenience
// of other Widgets classes. This header
// file may change from version to version
// without notice or even be removed.

namespace Widgets
{

/**
 * @internal
 * @short Builder interface
 *
 * This interface describes a builder, that
 * is used in the builder pattern.
 */
template <class T> class AbstractBuilder
{
public:
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~AbstractBuilder() {}
    /**
     * @internal
     * @brief Built element
     * @return built element.
     */
    inline T element() const {return builtElement;}
    /**
     * @internal
     * @brief Built the element
     *
     * This method is used to build the element.
     * Subclass this method to do the build task.
     */
    virtual void buildElement() = 0;
protected:
    /**
     * @internal
     * @brief Built element
     */
    T builtElement;
};

/**
 * @internal
 * @short Build manager
 *
 * This class is used to manage the build
 * of an element, using builders. It is
 * used in the builder pattern.
 */
template <class T> class BuildManager
{
public:
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~BuildManager() {}
    /**
     * @internal
     * @brief Set builder
     * @param builderToSet the builder to set.
     */
    inline void setBuilder(AbstractBuilder<T> *builderToSet) {builder = builderToSet;}
    /**
     * @internal
     * @brief Build
     */
    void build() {builder->buildElement();}
    /**
     * @internal
     * @brief Built element
     * @return built element.
     */
    inline T element() const {return builder->element();}
private:
    /**
     * @internal
     * @brief Builder
     */
    AbstractBuilder<T> *builder;
};


}

#endif // WIDGETS_BUILDERPATTERNINTERFACES_P_H
