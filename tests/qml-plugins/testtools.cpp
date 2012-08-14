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
 * @file testtools.cpp
 * @short Implementation of TestTools
 */

#include "testtools.h"
#include "tools.h"

#include <QtCore/QDebug>
#include <QtXml/QDomDocument>

void TestTools::testToolsBoolean_data()
{
    QTest::addColumn<QString>("boolString");
    QTest::addColumn<bool>("isTrue");

    QTest::newRow("true") << "true" << true;
    QTest::newRow("false") << "false" << false;
    QTest::newRow("true uppercase") << "True" << false;
    QTest::newRow("true uppercase") << "False" << false;
    QTest::newRow("invalid") << "dezdez" << false;
}


void TestTools::testToolsBoolean()
{
    QFETCH(QString, boolString);
    QFETCH(bool, isTrue);

    QCOMPARE (Widgets::Tools::stringToBool(boolString), isTrue);
}

void TestTools::testToolVariantHashXml()
{
    QVariantHash hash = QVariantHash();

    int anInteger = 213424532;
    double aDouble = 21321321.322131;
    QString aString = QString("nduiezjdez");

    hash.insert("an_integer", anInteger);
    hash.insert("a_double", aDouble);
    hash.insert("a_string", aString);
    hash.insert("bool_true", QVariant(true));
    hash.insert("bool_false", QVariant(false));

    QDomDocument document = QDomDocument();
    QDomElement element = Widgets::Tools::toXmlElementFromVariantMap(hash, "test", &document);
    QVariantHash convertedHash = Widgets::Tools::fromXmlElementToVariantMap(element);

    QCOMPARE(convertedHash.value("an_integer"), hash.value("an_integer"));
    QCOMPARE(convertedHash.value("a_double"), hash.value("a_double"));
    QCOMPARE(convertedHash.value("a_string"), hash.value("a_string"));
    QCOMPARE(convertedHash.value("bool_true"), hash.value("bool_true"));
    QCOMPARE(convertedHash.value("bool_false"), hash.value("bool_false"));
}

