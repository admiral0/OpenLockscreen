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

#ifndef WIDGETS_GLOBAL_H
#define WIDGETS_GLOBAL_H

/**
 * @file widgets_global.h
 * @short A set of global defines
 */

#include <QtCore/QtGlobal>

/**
 * @short Assert and execute
 *
 * This macro is similar to Q_ASSERT, but
 * always execute the asserted code. When
 * in debug mode, it uses Q_ASSERT to check
 * if the result is true, and in release mode
 * the code is executed without being checked.
 */
#if !defined(W_ASSERT)
#  ifndef QT_NO_DEBUG
#    define W_ASSERT(cond) Q_ASSERT(cond)
#  else
#    define W_ASSERT(cond) cond
#  endif
#endif

/**
 * @short Create the D-functions
 *
 * This macro is similar to Q_DECLARE_PRIVATE, but
 * use "d_pointer" and "d_function" instead of
 * "d_ptr" and "d_func" in order not to conflict with Qt
 * ones.
 */
#define W_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_function() { \
        return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_pointer)); \
    } \
    inline const Class##Private* d_function() const { \
        return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_pointer)); \
    } \
    friend class Class##Private;

/**
 * @short Get the D-pointer
 *
 * This macro is similar to Q_D, but
 * use "d_function" instead of "d_func"
 * in order not to conflict with Qt ones.
 */
#define W_D(Class) \
    Class##Private * const d = d_function()

#endif // WIDGETS_GLOBAL_H
