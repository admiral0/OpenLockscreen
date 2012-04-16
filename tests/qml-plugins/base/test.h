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

#ifndef TESTVERSION_H
#define TESTVERSION_H

#include <QtTest/QtTest>

class Test : public QObject
{
    Q_OBJECT
private slots:
    void testCreateVersion_data();
    void testCreateVersion();
    void testCompareVersion_data();
    void testCompareVersion();
    void testPackageManagerCreateTableAndUpdate();
    void testPackageManagerUpdate();
    void testPackageManagerDefault();
    void testPackageManagerGetPackage();
    void cleanupTestCase();
};

#endif // TESTVERSION_H
