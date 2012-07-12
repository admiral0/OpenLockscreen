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

#include "test.h"
#include "temporarypackagemanager.h"
#include "../../../qml-plugins/base/version.h"

void Test::testCreateVersion_data()
{
    QTest::addColumn<QString>("versionString");
    QTest::addColumn<bool>("valid");

    QTest::newRow("valid") << "12.431.2312" << true;
    QTest::newRow("invalid") << "a.c.v" << false;
    QTest::newRow("invalid_mixed") << "1.2.$" << false;
    QTest::newRow("invalid_with_other_caracters") << "jcio.dcscd?s\nhu.ds<ic\t" << false;
}

void Test::testCreateVersion()
{
    QFETCH(QString, versionString);
    QFETCH(bool, valid);

    Widgets::Version version = Widgets::Version::fromString(versionString);
    QCOMPARE(version.isValid(), valid);
}

void Test::testCompareVersion_data()
{
    QTest::addColumn<int>("version1Major");
    QTest::addColumn<int>("version1Minor");
    QTest::addColumn<int>("version1Patch");
    QTest::addColumn<int>("version2Major");
    QTest::addColumn<int>("version2Minor");
    QTest::addColumn<int>("version2Patch");
    QTest::addColumn<bool>("isEqual");
    QTest::addColumn<bool>("isLowerOrEqual");
    QTest::addColumn<bool>("isLower");
    QTest::addColumn<bool>("isGreaterOrEqual");
    QTest::addColumn<bool>("isGreater");

    QTest::newRow("1.0.0 <= and >= and == 1.0.1")
            << 1 << 0 << 0 << 1 << 0 << 1
            << true << true << false << true << false;
    QTest::newRow("1.1.0 > and >=  1.0.0")
            << 1 << 1 << 0 << 1 << 0 << 0
            << false << false << false << true << true;
    QTest::newRow("1.0.1 < and <=  1.1.0")
            << 1 << 0 << 1 << 1 << 1 << 0
            << false << true << true << false << false;
}

void Test::testCompareVersion()
{
    QFETCH(int, version1Major);
    QFETCH(int, version1Minor);
    QFETCH(int, version1Patch);
    QFETCH(int, version2Major);
    QFETCH(int, version2Minor);
    QFETCH(int, version2Patch);

    QFETCH(bool, isEqual);
    QFETCH(bool, isLowerOrEqual);
    QFETCH(bool, isLower);
    QFETCH(bool, isGreaterOrEqual);
    QFETCH(bool, isGreater);

    Widgets::Version version1 = Widgets::Version(version1Major, version1Minor, version1Patch);
    Widgets::Version version2 = Widgets::Version(version2Major, version2Minor, version2Patch);

    QCOMPARE(version1 == version2, isEqual);
    QCOMPARE(version1 <= version2, isLowerOrEqual);
    QCOMPARE(version1 < version2, isLower);
    QCOMPARE(version1 >= version2, isGreaterOrEqual);
    QCOMPARE(version1 > version2, isGreater);
}


void Test::testPackageManagerCreateTableAndUpdate()
{
    TemporaryPackageManager::deleteDb();
    QBENCHMARK_ONCE {
        TemporaryPackageManager packageManager;
        Q_UNUSED(packageManager)
    }
}

void Test::testPackageManagerUpdate()
{
    TemporaryPackageManager *packageManager = new TemporaryPackageManager;
    QBENCHMARK_ONCE {
        packageManager->update();
    }
}

void Test::testPackageManagerDefault()
{
    QBENCHMARK {
        TemporaryPackageManager packageManager;
        Q_UNUSED(packageManager)
    }
}

void Test::testPackageManagerGetPackage()
{
    TemporaryPackageManager packageManager;
    Widgets::Package package;
    QBENCHMARK {
        package = packageManager.package("org.SfietKonstantin.basicwidgets");
    }
    QCOMPARE(package.isValid(), true);
}

void Test::cleanupTestCase()
{
    TemporaryPackageManager::deleteDb();
}

QTEST_MAIN(Test)
