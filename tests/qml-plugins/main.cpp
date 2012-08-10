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

/**
 * @internal
 * @file tests/qml-plugins/main.cpp
 * @short Entry point of the tests for base
 */

#include <QtCore/QCoreApplication>

#include "testversion.h"
#include "testtools.h"
#include "testgraphicalcomponentbase.h"
#include "testwidgetproperties.h"
#include "testdockproperties.h"

/**
 * @internal
 * @short Main
 *
 * Entry point of the test application
 * that tests base widgets QML plugin.
 *
 * @param argc argc.
 * @param argv argv.
 * @return exit code.
 */
int main(int argc, char **argv)
{
    QCoreApplication app (argc, argv);
    Q_UNUSED(app)

    TestVersion testVersion;
    QTest::qExec(&testVersion, argc, argv);

    TestTools testTools;
    QTest::qExec(&testTools, argc, argv);

    TestGraphicalComponentBase testGraphicalComponentBase;
    QTest::qExec(&testGraphicalComponentBase, argc, argv);

    TestWidgetProperties testWidgetProperties;
    QTest::qExec(&testWidgetProperties, argc, argv);

    TestDockProperties testDockProperties;
    QTest::qExec(&testDockProperties, argc, argv);

    return 0;
}
