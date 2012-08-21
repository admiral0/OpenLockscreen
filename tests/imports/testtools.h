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

#ifndef TESTTOOLS_H
#define TESTTOOLS_H

/**
 * @internal
 * @file testtools.h
 * @short Definition of TestTools
 */

#include <QtTest/QtTest>

/**
 * @internal
 * @brief Tests for Widgets::Tools
 */
class TestTools : public QObject
{
    Q_OBJECT
private slots:
    /**
     * @internal
     * @brief Data for testToolsBoolean()
     */
    void testToolsBoolean_data();
    /**
     * @internal
     * @brief Test conversion from and to booleans
     *
     * This test is used to see
     * if the convertion from strings
     * to booleans is robust.
     */
    void testToolsBoolean();
    /**
     * @internal
     * @brief Test convertion from XML to variant hash
     *
     * This test is used to see
     * if the convertion from XML
     * elements to variant hash is robust.
     */
    void testToolVariantHashXml();
};

#endif // TESTTOOLS_H
