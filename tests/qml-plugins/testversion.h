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

#ifndef TESTVERSION_H
#define TESTVERSION_H

/**
 * @internal
 * @file testversion.h
 * @short Definition of TestVersion
 */

#include <QtTest/QTest>

/**
 * @internal
 * @brief Tests for Widgets::Version
 */
class TestVersion : public QObject
{
    Q_OBJECT
private slots:
    /**
     * @internal
     * @brief Data for testCreateVersion()
     */
    void testCreateVersion_data();
    /**
     * @internal
     * @brief Test version creation
     *
     * This test is used to see if the
     * version creation using strings
     * is robust.
     */
    void testCreateVersion();
    /**
     * @internal
     * @brief Data for testCompareVersion()
     */
    void testCompareVersion_data();
    /**
     * @internal
     * @brief Test version comparison
     *
     * This test is used to compare different
     * versions, and see if the comparison
     * operators work well.
     */
    void testCompareVersion();
};

#endif // TESTVERSION_H
