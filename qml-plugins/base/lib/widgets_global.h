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

#include <QtCore/QtGlobal>

#if !defined(W_ASSERT)
#  ifndef QT_NO_DEBUG
#    define W_ASSERT(cond) Q_ASSERT(cond)
#  else
#    define W_ASSERT(cond) cond
#  endif
#endif

#define W_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_function() { return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_pointer)); } \
    inline const Class##Private* d_function() const { return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_pointer)); } \
    friend class Class##Private;

#define W_D(Class) Class##Private * const d = d_function()

#endif // WIDGETS_GLOBAL_H
