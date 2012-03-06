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

/**
 * @file oxygencolors.h
 * @short Definition of Widgets::OxygenColors
 *
 * This file contains the definition of the
 * Widgets::OxygenColors class.
 */


#ifndef WIDGETS_OXYGENCOLORS_H
#define WIDGETS_OXYGENCOLORS_H

#include <QtCore/QObject>

namespace Widgets
{

/**
 * @short Base colors
 *
 * These colors are base colors that can be used
 * to provide a consistant theme for an
 * application.
 * 
 * These colors are extracted from KDE's oxygen color
 * palette.
 * 
 * This class is used in QML context. Accessing
 * it is done using the "colors" global object.
 *
 * @warning This code is generated with a script.
 */
class OxygenColors : public QObject
{
    Q_OBJECT

    /**
     * @short Color woodBrown6
     */
    Q_PROPERTY(QString woodBrown6 READ woodBrown6 CONSTANT )
    /**
     * @short Color woodBrown5
     */
    Q_PROPERTY(QString woodBrown5 READ woodBrown5 CONSTANT )
    /**
     * @short Color woodBrown4
     */
    Q_PROPERTY(QString woodBrown4 READ woodBrown4 CONSTANT )
    /**
     * @short Color woodBrown3
     */
    Q_PROPERTY(QString woodBrown3 READ woodBrown3 CONSTANT )
    /**
     * @short Color woodBrown2
     */
    Q_PROPERTY(QString woodBrown2 READ woodBrown2 CONSTANT )
    /**
     * @short Color woodBrown1
     */
    Q_PROPERTY(QString woodBrown1 READ woodBrown1 CONSTANT )
    /**
     * @short Color brickRed6
     */
    Q_PROPERTY(QString brickRed6 READ brickRed6 CONSTANT )
    /**
     * @short Color brickRed5
     */
    Q_PROPERTY(QString brickRed5 READ brickRed5 CONSTANT )
    /**
     * @short Color brickRed4
     */
    Q_PROPERTY(QString brickRed4 READ brickRed4 CONSTANT )
    /**
     * @short Color brickRed3
     */
    Q_PROPERTY(QString brickRed3 READ brickRed3 CONSTANT )
    /**
     * @short Color brickRed2
     */
    Q_PROPERTY(QString brickRed2 READ brickRed2 CONSTANT )
    /**
     * @short Color brickRed1
     */
    Q_PROPERTY(QString brickRed1 READ brickRed1 CONSTANT )
    /**
     * @short Color raspberryPink6
     */
    Q_PROPERTY(QString raspberryPink6 READ raspberryPink6 CONSTANT )
    /**
     * @short Color raspberryPink5
     */
    Q_PROPERTY(QString raspberryPink5 READ raspberryPink5 CONSTANT )
    /**
     * @short Color raspberryPink4
     */
    Q_PROPERTY(QString raspberryPink4 READ raspberryPink4 CONSTANT )
    /**
     * @short Color raspberryPink3
     */
    Q_PROPERTY(QString raspberryPink3 READ raspberryPink3 CONSTANT )
    /**
     * @short Color raspberryPink2
     */
    Q_PROPERTY(QString raspberryPink2 READ raspberryPink2 CONSTANT )
    /**
     * @short Color raspberryPink1
     */
    Q_PROPERTY(QString raspberryPink1 READ raspberryPink1 CONSTANT )
    /**
     * @short Color burgundyPurple6
     */
    Q_PROPERTY(QString burgundyPurple6 READ burgundyPurple6 CONSTANT )
    /**
     * @short Color burgundyPurple5
     */
    Q_PROPERTY(QString burgundyPurple5 READ burgundyPurple5 CONSTANT )
    /**
     * @short Color burgundyPurple4
     */
    Q_PROPERTY(QString burgundyPurple4 READ burgundyPurple4 CONSTANT )
    /**
     * @short Color burgundyPurple3
     */
    Q_PROPERTY(QString burgundyPurple3 READ burgundyPurple3 CONSTANT )
    /**
     * @short Color burgundyPurple2
     */
    Q_PROPERTY(QString burgundyPurple2 READ burgundyPurple2 CONSTANT )
    /**
     * @short Color burgundyPurple1
     */
    Q_PROPERTY(QString burgundyPurple1 READ burgundyPurple1 CONSTANT )
    /**
     * @short Color grapeViolet6
     */
    Q_PROPERTY(QString grapeViolet6 READ grapeViolet6 CONSTANT )
    /**
     * @short Color grapeViolet5
     */
    Q_PROPERTY(QString grapeViolet5 READ grapeViolet5 CONSTANT )
    /**
     * @short Color grapeViolet4
     */
    Q_PROPERTY(QString grapeViolet4 READ grapeViolet4 CONSTANT )
    /**
     * @short Color grapeViolet3
     */
    Q_PROPERTY(QString grapeViolet3 READ grapeViolet3 CONSTANT )
    /**
     * @short Color grapeViolet2
     */
    Q_PROPERTY(QString grapeViolet2 READ grapeViolet2 CONSTANT )
    /**
     * @short Color grapeViolet1
     */
    Q_PROPERTY(QString grapeViolet1 READ grapeViolet1 CONSTANT )
    /**
     * @short Color skyBlue6
     */
    Q_PROPERTY(QString skyBlue6 READ skyBlue6 CONSTANT )
    /**
     * @short Color skyBlue5
     */
    Q_PROPERTY(QString skyBlue5 READ skyBlue5 CONSTANT )
    /**
     * @short Color skyBlue4
     */
    Q_PROPERTY(QString skyBlue4 READ skyBlue4 CONSTANT )
    /**
     * @short Color skyBlue3
     */
    Q_PROPERTY(QString skyBlue3 READ skyBlue3 CONSTANT )
    /**
     * @short Color skyBlue2
     */
    Q_PROPERTY(QString skyBlue2 READ skyBlue2 CONSTANT )
    /**
     * @short Color skyBlue1
     */
    Q_PROPERTY(QString skyBlue1 READ skyBlue1 CONSTANT )
    /**
     * @short Color seaBlue6
     */
    Q_PROPERTY(QString seaBlue6 READ seaBlue6 CONSTANT )
    /**
     * @short Color seaBlue5
     */
    Q_PROPERTY(QString seaBlue5 READ seaBlue5 CONSTANT )
    /**
     * @short Color seaBlue4
     */
    Q_PROPERTY(QString seaBlue4 READ seaBlue4 CONSTANT )
    /**
     * @short Color seaBlue3
     */
    Q_PROPERTY(QString seaBlue3 READ seaBlue3 CONSTANT )
    /**
     * @short Color seaBlue2
     */
    Q_PROPERTY(QString seaBlue2 READ seaBlue2 CONSTANT )
    /**
     * @short Color seaBlue1
     */
    Q_PROPERTY(QString seaBlue1 READ seaBlue1 CONSTANT )
    /**
     * @short Color emeraldGreen6
     */
    Q_PROPERTY(QString emeraldGreen6 READ emeraldGreen6 CONSTANT )
    /**
     * @short Color emeraldGreen5
     */
    Q_PROPERTY(QString emeraldGreen5 READ emeraldGreen5 CONSTANT )
    /**
     * @short Color emeraldGreen4
     */
    Q_PROPERTY(QString emeraldGreen4 READ emeraldGreen4 CONSTANT )
    /**
     * @short Color emeraldGreen3
     */
    Q_PROPERTY(QString emeraldGreen3 READ emeraldGreen3 CONSTANT )
    /**
     * @short Color emeraldGreen2
     */
    Q_PROPERTY(QString emeraldGreen2 READ emeraldGreen2 CONSTANT )
    /**
     * @short Color emeraldGreen1
     */
    Q_PROPERTY(QString emeraldGreen1 READ emeraldGreen1 CONSTANT )
    /**
     * @short Color forestGreen6
     */
    Q_PROPERTY(QString forestGreen6 READ forestGreen6 CONSTANT )
    /**
     * @short Color forestGreen5
     */
    Q_PROPERTY(QString forestGreen5 READ forestGreen5 CONSTANT )
    /**
     * @short Color forestGreen4
     */
    Q_PROPERTY(QString forestGreen4 READ forestGreen4 CONSTANT )
    /**
     * @short Color forestGreen3
     */
    Q_PROPERTY(QString forestGreen3 READ forestGreen3 CONSTANT )
    /**
     * @short Color forestGreen2
     */
    Q_PROPERTY(QString forestGreen2 READ forestGreen2 CONSTANT )
    /**
     * @short Color forestGreen1
     */
    Q_PROPERTY(QString forestGreen1 READ forestGreen1 CONSTANT )
    /**
     * @short Color sunYellow6
     */
    Q_PROPERTY(QString sunYellow6 READ sunYellow6 CONSTANT )
    /**
     * @short Color sunYellow5
     */
    Q_PROPERTY(QString sunYellow5 READ sunYellow5 CONSTANT )
    /**
     * @short Color sunYellow4
     */
    Q_PROPERTY(QString sunYellow4 READ sunYellow4 CONSTANT )
    /**
     * @short Color sunYellow3
     */
    Q_PROPERTY(QString sunYellow3 READ sunYellow3 CONSTANT )
    /**
     * @short Color sunYellow2
     */
    Q_PROPERTY(QString sunYellow2 READ sunYellow2 CONSTANT )
    /**
     * @short Color sunYellow1
     */
    Q_PROPERTY(QString sunYellow1 READ sunYellow1 CONSTANT )
    /**
     * @short Color hotOrange6
     */
    Q_PROPERTY(QString hotOrange6 READ hotOrange6 CONSTANT )
    /**
     * @short Color hotOrange5
     */
    Q_PROPERTY(QString hotOrange5 READ hotOrange5 CONSTANT )
    /**
     * @short Color hotOrange4
     */
    Q_PROPERTY(QString hotOrange4 READ hotOrange4 CONSTANT )
    /**
     * @short Color hotOrange3
     */
    Q_PROPERTY(QString hotOrange3 READ hotOrange3 CONSTANT )
    /**
     * @short Color hotOrange2
     */
    Q_PROPERTY(QString hotOrange2 READ hotOrange2 CONSTANT )
    /**
     * @short Color hotOrange1
     */
    Q_PROPERTY(QString hotOrange1 READ hotOrange1 CONSTANT )
    /**
     * @short Color aluminiumGray6
     */
    Q_PROPERTY(QString aluminiumGray6 READ aluminiumGray6 CONSTANT )
    /**
     * @short Color aluminiumGray5
     */
    Q_PROPERTY(QString aluminiumGray5 READ aluminiumGray5 CONSTANT )
    /**
     * @short Color aluminiumGray4
     */
    Q_PROPERTY(QString aluminiumGray4 READ aluminiumGray4 CONSTANT )
    /**
     * @short Color aluminiumGray3
     */
    Q_PROPERTY(QString aluminiumGray3 READ aluminiumGray3 CONSTANT )
    /**
     * @short Color aluminiumGray2
     */
    Q_PROPERTY(QString aluminiumGray2 READ aluminiumGray2 CONSTANT )
    /**
     * @short Color aluminiumGray1
     */
    Q_PROPERTY(QString aluminiumGray1 READ aluminiumGray1 CONSTANT )
    /**
     * @short Color brownOrange6
     */
    Q_PROPERTY(QString brownOrange6 READ brownOrange6 CONSTANT )
    /**
     * @short Color brownOrange5
     */
    Q_PROPERTY(QString brownOrange5 READ brownOrange5 CONSTANT )
    /**
     * @short Color brownOrange4
     */
    Q_PROPERTY(QString brownOrange4 READ brownOrange4 CONSTANT )
    /**
     * @short Color brownOrange3
     */
    Q_PROPERTY(QString brownOrange3 READ brownOrange3 CONSTANT )
    /**
     * @short Color brownOrange2
     */
    Q_PROPERTY(QString brownOrange2 READ brownOrange2 CONSTANT )
    /**
     * @short Color brownOrange1
     */
    Q_PROPERTY(QString brownOrange1 READ brownOrange1 CONSTANT )
    /**
     * @short Color red6
     */
    Q_PROPERTY(QString red6 READ red6 CONSTANT )
    /**
     * @short Color red5
     */
    Q_PROPERTY(QString red5 READ red5 CONSTANT )
    /**
     * @short Color red4
     */
    Q_PROPERTY(QString red4 READ red4 CONSTANT )
    /**
     * @short Color red3
     */
    Q_PROPERTY(QString red3 READ red3 CONSTANT )
    /**
     * @short Color red2
     */
    Q_PROPERTY(QString red2 READ red2 CONSTANT )
    /**
     * @short Color red1
     */
    Q_PROPERTY(QString red1 READ red1 CONSTANT )
    /**
     * @short Color pink6
     */
    Q_PROPERTY(QString pink6 READ pink6 CONSTANT )
    /**
     * @short Color pink5
     */
    Q_PROPERTY(QString pink5 READ pink5 CONSTANT )
    /**
     * @short Color pink4
     */
    Q_PROPERTY(QString pink4 READ pink4 CONSTANT )
    /**
     * @short Color pink3
     */
    Q_PROPERTY(QString pink3 READ pink3 CONSTANT )
    /**
     * @short Color pink2
     */
    Q_PROPERTY(QString pink2 READ pink2 CONSTANT )
    /**
     * @short Color pink1
     */
    Q_PROPERTY(QString pink1 READ pink1 CONSTANT )
    /**
     * @short Color purple6
     */
    Q_PROPERTY(QString purple6 READ purple6 CONSTANT )
    /**
     * @short Color purple5
     */
    Q_PROPERTY(QString purple5 READ purple5 CONSTANT )
    /**
     * @short Color purple4
     */
    Q_PROPERTY(QString purple4 READ purple4 CONSTANT )
    /**
     * @short Color purple3
     */
    Q_PROPERTY(QString purple3 READ purple3 CONSTANT )
    /**
     * @short Color purple2
     */
    Q_PROPERTY(QString purple2 READ purple2 CONSTANT )
    /**
     * @short Color purple1
     */
    Q_PROPERTY(QString purple1 READ purple1 CONSTANT )
    /**
     * @short Color blue6
     */
    Q_PROPERTY(QString blue6 READ blue6 CONSTANT )
    /**
     * @short Color blue5
     */
    Q_PROPERTY(QString blue5 READ blue5 CONSTANT )
    /**
     * @short Color blue4
     */
    Q_PROPERTY(QString blue4 READ blue4 CONSTANT )
    /**
     * @short Color blue3
     */
    Q_PROPERTY(QString blue3 READ blue3 CONSTANT )
    /**
     * @short Color blue2
     */
    Q_PROPERTY(QString blue2 READ blue2 CONSTANT )
    /**
     * @short Color blue1
     */
    Q_PROPERTY(QString blue1 READ blue1 CONSTANT )
    /**
     * @short Color green6
     */
    Q_PROPERTY(QString green6 READ green6 CONSTANT )
    /**
     * @short Color green5
     */
    Q_PROPERTY(QString green5 READ green5 CONSTANT )
    /**
     * @short Color green4
     */
    Q_PROPERTY(QString green4 READ green4 CONSTANT )
    /**
     * @short Color green3
     */
    Q_PROPERTY(QString green3 READ green3 CONSTANT )
    /**
     * @short Color green2
     */
    Q_PROPERTY(QString green2 READ green2 CONSTANT )
    /**
     * @short Color green1
     */
    Q_PROPERTY(QString green1 READ green1 CONSTANT )
    /**
     * @short Color lime6
     */
    Q_PROPERTY(QString lime6 READ lime6 CONSTANT )
    /**
     * @short Color lime5
     */
    Q_PROPERTY(QString lime5 READ lime5 CONSTANT )
    /**
     * @short Color lime4
     */
    Q_PROPERTY(QString lime4 READ lime4 CONSTANT )
    /**
     * @short Color lime3
     */
    Q_PROPERTY(QString lime3 READ lime3 CONSTANT )
    /**
     * @short Color lime2
     */
    Q_PROPERTY(QString lime2 READ lime2 CONSTANT )
    /**
     * @short Color lime1
     */
    Q_PROPERTY(QString lime1 READ lime1 CONSTANT )
    /**
     * @short Color yellow6
     */
    Q_PROPERTY(QString yellow6 READ yellow6 CONSTANT )
    /**
     * @short Color yellow5
     */
    Q_PROPERTY(QString yellow5 READ yellow5 CONSTANT )
    /**
     * @short Color yellow4
     */
    Q_PROPERTY(QString yellow4 READ yellow4 CONSTANT )
    /**
     * @short Color yellow3
     */
    Q_PROPERTY(QString yellow3 READ yellow3 CONSTANT )
    /**
     * @short Color yellow2
     */
    Q_PROPERTY(QString yellow2 READ yellow2 CONSTANT )
    /**
     * @short Color yellow1
     */
    Q_PROPERTY(QString yellow1 READ yellow1 CONSTANT )
    /**
     * @short Color gray6
     */
    Q_PROPERTY(QString gray6 READ gray6 CONSTANT )
    /**
     * @short Color gray5
     */
    Q_PROPERTY(QString gray5 READ gray5 CONSTANT )
    /**
     * @short Color gray4
     */
    Q_PROPERTY(QString gray4 READ gray4 CONSTANT )
    /**
     * @short Color gray3
     */
    Q_PROPERTY(QString gray3 READ gray3 CONSTANT )
    /**
     * @short Color gray2
     */
    Q_PROPERTY(QString gray2 READ gray2 CONSTANT )
    /**
     * @short Color gray1
     */
    Q_PROPERTY(QString gray1 READ gray1 CONSTANT )
    /**
     * @short Color white
     */
    Q_PROPERTY(QString white READ white CONSTANT )
    /**
     * @short Color black
     */
    Q_PROPERTY(QString black READ black CONSTANT )

public:
    /**
     * @short Color woodBrown6
     *
     * This method returns the color code for woodBrown6.
     *
     * @return the color code for woodBrown6
     */
    QString woodBrown6() const;
    /**
     * @short Color woodBrown5
     *
     * This method returns the color code for woodBrown5.
     *
     * @return the color code for woodBrown5
     */
    QString woodBrown5() const;
    /**
     * @short Color woodBrown4
     *
     * This method returns the color code for woodBrown4.
     *
     * @return the color code for woodBrown4
     */
    QString woodBrown4() const;
    /**
     * @short Color woodBrown3
     *
     * This method returns the color code for woodBrown3.
     *
     * @return the color code for woodBrown3
     */
    QString woodBrown3() const;
    /**
     * @short Color woodBrown2
     *
     * This method returns the color code for woodBrown2.
     *
     * @return the color code for woodBrown2
     */
    QString woodBrown2() const;
    /**
     * @short Color woodBrown1
     *
     * This method returns the color code for woodBrown1.
     *
     * @return the color code for woodBrown1
     */
    QString woodBrown1() const;
    /**
     * @short Color brickRed6
     *
     * This method returns the color code for brickRed6.
     *
     * @return the color code for brickRed6
     */
    QString brickRed6() const;
    /**
     * @short Color brickRed5
     *
     * This method returns the color code for brickRed5.
     *
     * @return the color code for brickRed5
     */
    QString brickRed5() const;
    /**
     * @short Color brickRed4
     *
     * This method returns the color code for brickRed4.
     *
     * @return the color code for brickRed4
     */
    QString brickRed4() const;
    /**
     * @short Color brickRed3
     *
     * This method returns the color code for brickRed3.
     *
     * @return the color code for brickRed3
     */
    QString brickRed3() const;
    /**
     * @short Color brickRed2
     *
     * This method returns the color code for brickRed2.
     *
     * @return the color code for brickRed2
     */
    QString brickRed2() const;
    /**
     * @short Color brickRed1
     *
     * This method returns the color code for brickRed1.
     *
     * @return the color code for brickRed1
     */
    QString brickRed1() const;
    /**
     * @short Color raspberryPink6
     *
     * This method returns the color code for raspberryPink6.
     *
     * @return the color code for raspberryPink6
     */
    QString raspberryPink6() const;
    /**
     * @short Color raspberryPink5
     *
     * This method returns the color code for raspberryPink5.
     *
     * @return the color code for raspberryPink5
     */
    QString raspberryPink5() const;
    /**
     * @short Color raspberryPink4
     *
     * This method returns the color code for raspberryPink4.
     *
     * @return the color code for raspberryPink4
     */
    QString raspberryPink4() const;
    /**
     * @short Color raspberryPink3
     *
     * This method returns the color code for raspberryPink3.
     *
     * @return the color code for raspberryPink3
     */
    QString raspberryPink3() const;
    /**
     * @short Color raspberryPink2
     *
     * This method returns the color code for raspberryPink2.
     *
     * @return the color code for raspberryPink2
     */
    QString raspberryPink2() const;
    /**
     * @short Color raspberryPink1
     *
     * This method returns the color code for raspberryPink1.
     *
     * @return the color code for raspberryPink1
     */
    QString raspberryPink1() const;
    /**
     * @short Color burgundyPurple6
     *
     * This method returns the color code for burgundyPurple6.
     *
     * @return the color code for burgundyPurple6
     */
    QString burgundyPurple6() const;
    /**
     * @short Color burgundyPurple5
     *
     * This method returns the color code for burgundyPurple5.
     *
     * @return the color code for burgundyPurple5
     */
    QString burgundyPurple5() const;
    /**
     * @short Color burgundyPurple4
     *
     * This method returns the color code for burgundyPurple4.
     *
     * @return the color code for burgundyPurple4
     */
    QString burgundyPurple4() const;
    /**
     * @short Color burgundyPurple3
     *
     * This method returns the color code for burgundyPurple3.
     *
     * @return the color code for burgundyPurple3
     */
    QString burgundyPurple3() const;
    /**
     * @short Color burgundyPurple2
     *
     * This method returns the color code for burgundyPurple2.
     *
     * @return the color code for burgundyPurple2
     */
    QString burgundyPurple2() const;
    /**
     * @short Color burgundyPurple1
     *
     * This method returns the color code for burgundyPurple1.
     *
     * @return the color code for burgundyPurple1
     */
    QString burgundyPurple1() const;
    /**
     * @short Color grapeViolet6
     *
     * This method returns the color code for grapeViolet6.
     *
     * @return the color code for grapeViolet6
     */
    QString grapeViolet6() const;
    /**
     * @short Color grapeViolet5
     *
     * This method returns the color code for grapeViolet5.
     *
     * @return the color code for grapeViolet5
     */
    QString grapeViolet5() const;
    /**
     * @short Color grapeViolet4
     *
     * This method returns the color code for grapeViolet4.
     *
     * @return the color code for grapeViolet4
     */
    QString grapeViolet4() const;
    /**
     * @short Color grapeViolet3
     *
     * This method returns the color code for grapeViolet3.
     *
     * @return the color code for grapeViolet3
     */
    QString grapeViolet3() const;
    /**
     * @short Color grapeViolet2
     *
     * This method returns the color code for grapeViolet2.
     *
     * @return the color code for grapeViolet2
     */
    QString grapeViolet2() const;
    /**
     * @short Color grapeViolet1
     *
     * This method returns the color code for grapeViolet1.
     *
     * @return the color code for grapeViolet1
     */
    QString grapeViolet1() const;
    /**
     * @short Color skyBlue6
     *
     * This method returns the color code for skyBlue6.
     *
     * @return the color code for skyBlue6
     */
    QString skyBlue6() const;
    /**
     * @short Color skyBlue5
     *
     * This method returns the color code for skyBlue5.
     *
     * @return the color code for skyBlue5
     */
    QString skyBlue5() const;
    /**
     * @short Color skyBlue4
     *
     * This method returns the color code for skyBlue4.
     *
     * @return the color code for skyBlue4
     */
    QString skyBlue4() const;
    /**
     * @short Color skyBlue3
     *
     * This method returns the color code for skyBlue3.
     *
     * @return the color code for skyBlue3
     */
    QString skyBlue3() const;
    /**
     * @short Color skyBlue2
     *
     * This method returns the color code for skyBlue2.
     *
     * @return the color code for skyBlue2
     */
    QString skyBlue2() const;
    /**
     * @short Color skyBlue1
     *
     * This method returns the color code for skyBlue1.
     *
     * @return the color code for skyBlue1
     */
    QString skyBlue1() const;
    /**
     * @short Color seaBlue6
     *
     * This method returns the color code for seaBlue6.
     *
     * @return the color code for seaBlue6
     */
    QString seaBlue6() const;
    /**
     * @short Color seaBlue5
     *
     * This method returns the color code for seaBlue5.
     *
     * @return the color code for seaBlue5
     */
    QString seaBlue5() const;
    /**
     * @short Color seaBlue4
     *
     * This method returns the color code for seaBlue4.
     *
     * @return the color code for seaBlue4
     */
    QString seaBlue4() const;
    /**
     * @short Color seaBlue3
     *
     * This method returns the color code for seaBlue3.
     *
     * @return the color code for seaBlue3
     */
    QString seaBlue3() const;
    /**
     * @short Color seaBlue2
     *
     * This method returns the color code for seaBlue2.
     *
     * @return the color code for seaBlue2
     */
    QString seaBlue2() const;
    /**
     * @short Color seaBlue1
     *
     * This method returns the color code for seaBlue1.
     *
     * @return the color code for seaBlue1
     */
    QString seaBlue1() const;
    /**
     * @short Color emeraldGreen6
     *
     * This method returns the color code for emeraldGreen6.
     *
     * @return the color code for emeraldGreen6
     */
    QString emeraldGreen6() const;
    /**
     * @short Color emeraldGreen5
     *
     * This method returns the color code for emeraldGreen5.
     *
     * @return the color code for emeraldGreen5
     */
    QString emeraldGreen5() const;
    /**
     * @short Color emeraldGreen4
     *
     * This method returns the color code for emeraldGreen4.
     *
     * @return the color code for emeraldGreen4
     */
    QString emeraldGreen4() const;
    /**
     * @short Color emeraldGreen3
     *
     * This method returns the color code for emeraldGreen3.
     *
     * @return the color code for emeraldGreen3
     */
    QString emeraldGreen3() const;
    /**
     * @short Color emeraldGreen2
     *
     * This method returns the color code for emeraldGreen2.
     *
     * @return the color code for emeraldGreen2
     */
    QString emeraldGreen2() const;
    /**
     * @short Color emeraldGreen1
     *
     * This method returns the color code for emeraldGreen1.
     *
     * @return the color code for emeraldGreen1
     */
    QString emeraldGreen1() const;
    /**
     * @short Color forestGreen6
     *
     * This method returns the color code for forestGreen6.
     *
     * @return the color code for forestGreen6
     */
    QString forestGreen6() const;
    /**
     * @short Color forestGreen5
     *
     * This method returns the color code for forestGreen5.
     *
     * @return the color code for forestGreen5
     */
    QString forestGreen5() const;
    /**
     * @short Color forestGreen4
     *
     * This method returns the color code for forestGreen4.
     *
     * @return the color code for forestGreen4
     */
    QString forestGreen4() const;
    /**
     * @short Color forestGreen3
     *
     * This method returns the color code for forestGreen3.
     *
     * @return the color code for forestGreen3
     */
    QString forestGreen3() const;
    /**
     * @short Color forestGreen2
     *
     * This method returns the color code for forestGreen2.
     *
     * @return the color code for forestGreen2
     */
    QString forestGreen2() const;
    /**
     * @short Color forestGreen1
     *
     * This method returns the color code for forestGreen1.
     *
     * @return the color code for forestGreen1
     */
    QString forestGreen1() const;
    /**
     * @short Color sunYellow6
     *
     * This method returns the color code for sunYellow6.
     *
     * @return the color code for sunYellow6
     */
    QString sunYellow6() const;
    /**
     * @short Color sunYellow5
     *
     * This method returns the color code for sunYellow5.
     *
     * @return the color code for sunYellow5
     */
    QString sunYellow5() const;
    /**
     * @short Color sunYellow4
     *
     * This method returns the color code for sunYellow4.
     *
     * @return the color code for sunYellow4
     */
    QString sunYellow4() const;
    /**
     * @short Color sunYellow3
     *
     * This method returns the color code for sunYellow3.
     *
     * @return the color code for sunYellow3
     */
    QString sunYellow3() const;
    /**
     * @short Color sunYellow2
     *
     * This method returns the color code for sunYellow2.
     *
     * @return the color code for sunYellow2
     */
    QString sunYellow2() const;
    /**
     * @short Color sunYellow1
     *
     * This method returns the color code for sunYellow1.
     *
     * @return the color code for sunYellow1
     */
    QString sunYellow1() const;
    /**
     * @short Color hotOrange6
     *
     * This method returns the color code for hotOrange6.
     *
     * @return the color code for hotOrange6
     */
    QString hotOrange6() const;
    /**
     * @short Color hotOrange5
     *
     * This method returns the color code for hotOrange5.
     *
     * @return the color code for hotOrange5
     */
    QString hotOrange5() const;
    /**
     * @short Color hotOrange4
     *
     * This method returns the color code for hotOrange4.
     *
     * @return the color code for hotOrange4
     */
    QString hotOrange4() const;
    /**
     * @short Color hotOrange3
     *
     * This method returns the color code for hotOrange3.
     *
     * @return the color code for hotOrange3
     */
    QString hotOrange3() const;
    /**
     * @short Color hotOrange2
     *
     * This method returns the color code for hotOrange2.
     *
     * @return the color code for hotOrange2
     */
    QString hotOrange2() const;
    /**
     * @short Color hotOrange1
     *
     * This method returns the color code for hotOrange1.
     *
     * @return the color code for hotOrange1
     */
    QString hotOrange1() const;
    /**
     * @short Color aluminiumGray6
     *
     * This method returns the color code for aluminiumGray6.
     *
     * @return the color code for aluminiumGray6
     */
    QString aluminiumGray6() const;
    /**
     * @short Color aluminiumGray5
     *
     * This method returns the color code for aluminiumGray5.
     *
     * @return the color code for aluminiumGray5
     */
    QString aluminiumGray5() const;
    /**
     * @short Color aluminiumGray4
     *
     * This method returns the color code for aluminiumGray4.
     *
     * @return the color code for aluminiumGray4
     */
    QString aluminiumGray4() const;
    /**
     * @short Color aluminiumGray3
     *
     * This method returns the color code for aluminiumGray3.
     *
     * @return the color code for aluminiumGray3
     */
    QString aluminiumGray3() const;
    /**
     * @short Color aluminiumGray2
     *
     * This method returns the color code for aluminiumGray2.
     *
     * @return the color code for aluminiumGray2
     */
    QString aluminiumGray2() const;
    /**
     * @short Color aluminiumGray1
     *
     * This method returns the color code for aluminiumGray1.
     *
     * @return the color code for aluminiumGray1
     */
    QString aluminiumGray1() const;
    /**
     * @short Color brownOrange6
     *
     * This method returns the color code for brownOrange6.
     *
     * @return the color code for brownOrange6
     */
    QString brownOrange6() const;
    /**
     * @short Color brownOrange5
     *
     * This method returns the color code for brownOrange5.
     *
     * @return the color code for brownOrange5
     */
    QString brownOrange5() const;
    /**
     * @short Color brownOrange4
     *
     * This method returns the color code for brownOrange4.
     *
     * @return the color code for brownOrange4
     */
    QString brownOrange4() const;
    /**
     * @short Color brownOrange3
     *
     * This method returns the color code for brownOrange3.
     *
     * @return the color code for brownOrange3
     */
    QString brownOrange3() const;
    /**
     * @short Color brownOrange2
     *
     * This method returns the color code for brownOrange2.
     *
     * @return the color code for brownOrange2
     */
    QString brownOrange2() const;
    /**
     * @short Color brownOrange1
     *
     * This method returns the color code for brownOrange1.
     *
     * @return the color code for brownOrange1
     */
    QString brownOrange1() const;
    /**
     * @short Color red6
     *
     * This method returns the color code for red6.
     *
     * @return the color code for red6
     */
    QString red6() const;
    /**
     * @short Color red5
     *
     * This method returns the color code for red5.
     *
     * @return the color code for red5
     */
    QString red5() const;
    /**
     * @short Color red4
     *
     * This method returns the color code for red4.
     *
     * @return the color code for red4
     */
    QString red4() const;
    /**
     * @short Color red3
     *
     * This method returns the color code for red3.
     *
     * @return the color code for red3
     */
    QString red3() const;
    /**
     * @short Color red2
     *
     * This method returns the color code for red2.
     *
     * @return the color code for red2
     */
    QString red2() const;
    /**
     * @short Color red1
     *
     * This method returns the color code for red1.
     *
     * @return the color code for red1
     */
    QString red1() const;
    /**
     * @short Color pink6
     *
     * This method returns the color code for pink6.
     *
     * @return the color code for pink6
     */
    QString pink6() const;
    /**
     * @short Color pink5
     *
     * This method returns the color code for pink5.
     *
     * @return the color code for pink5
     */
    QString pink5() const;
    /**
     * @short Color pink4
     *
     * This method returns the color code for pink4.
     *
     * @return the color code for pink4
     */
    QString pink4() const;
    /**
     * @short Color pink3
     *
     * This method returns the color code for pink3.
     *
     * @return the color code for pink3
     */
    QString pink3() const;
    /**
     * @short Color pink2
     *
     * This method returns the color code for pink2.
     *
     * @return the color code for pink2
     */
    QString pink2() const;
    /**
     * @short Color pink1
     *
     * This method returns the color code for pink1.
     *
     * @return the color code for pink1
     */
    QString pink1() const;
    /**
     * @short Color purple6
     *
     * This method returns the color code for purple6.
     *
     * @return the color code for purple6
     */
    QString purple6() const;
    /**
     * @short Color purple5
     *
     * This method returns the color code for purple5.
     *
     * @return the color code for purple5
     */
    QString purple5() const;
    /**
     * @short Color purple4
     *
     * This method returns the color code for purple4.
     *
     * @return the color code for purple4
     */
    QString purple4() const;
    /**
     * @short Color purple3
     *
     * This method returns the color code for purple3.
     *
     * @return the color code for purple3
     */
    QString purple3() const;
    /**
     * @short Color purple2
     *
     * This method returns the color code for purple2.
     *
     * @return the color code for purple2
     */
    QString purple2() const;
    /**
     * @short Color purple1
     *
     * This method returns the color code for purple1.
     *
     * @return the color code for purple1
     */
    QString purple1() const;
    /**
     * @short Color blue6
     *
     * This method returns the color code for blue6.
     *
     * @return the color code for blue6
     */
    QString blue6() const;
    /**
     * @short Color blue5
     *
     * This method returns the color code for blue5.
     *
     * @return the color code for blue5
     */
    QString blue5() const;
    /**
     * @short Color blue4
     *
     * This method returns the color code for blue4.
     *
     * @return the color code for blue4
     */
    QString blue4() const;
    /**
     * @short Color blue3
     *
     * This method returns the color code for blue3.
     *
     * @return the color code for blue3
     */
    QString blue3() const;
    /**
     * @short Color blue2
     *
     * This method returns the color code for blue2.
     *
     * @return the color code for blue2
     */
    QString blue2() const;
    /**
     * @short Color blue1
     *
     * This method returns the color code for blue1.
     *
     * @return the color code for blue1
     */
    QString blue1() const;
    /**
     * @short Color green6
     *
     * This method returns the color code for green6.
     *
     * @return the color code for green6
     */
    QString green6() const;
    /**
     * @short Color green5
     *
     * This method returns the color code for green5.
     *
     * @return the color code for green5
     */
    QString green5() const;
    /**
     * @short Color green4
     *
     * This method returns the color code for green4.
     *
     * @return the color code for green4
     */
    QString green4() const;
    /**
     * @short Color green3
     *
     * This method returns the color code for green3.
     *
     * @return the color code for green3
     */
    QString green3() const;
    /**
     * @short Color green2
     *
     * This method returns the color code for green2.
     *
     * @return the color code for green2
     */
    QString green2() const;
    /**
     * @short Color green1
     *
     * This method returns the color code for green1.
     *
     * @return the color code for green1
     */
    QString green1() const;
    /**
     * @short Color lime6
     *
     * This method returns the color code for lime6.
     *
     * @return the color code for lime6
     */
    QString lime6() const;
    /**
     * @short Color lime5
     *
     * This method returns the color code for lime5.
     *
     * @return the color code for lime5
     */
    QString lime5() const;
    /**
     * @short Color lime4
     *
     * This method returns the color code for lime4.
     *
     * @return the color code for lime4
     */
    QString lime4() const;
    /**
     * @short Color lime3
     *
     * This method returns the color code for lime3.
     *
     * @return the color code for lime3
     */
    QString lime3() const;
    /**
     * @short Color lime2
     *
     * This method returns the color code for lime2.
     *
     * @return the color code for lime2
     */
    QString lime2() const;
    /**
     * @short Color lime1
     *
     * This method returns the color code for lime1.
     *
     * @return the color code for lime1
     */
    QString lime1() const;
    /**
     * @short Color yellow6
     *
     * This method returns the color code for yellow6.
     *
     * @return the color code for yellow6
     */
    QString yellow6() const;
    /**
     * @short Color yellow5
     *
     * This method returns the color code for yellow5.
     *
     * @return the color code for yellow5
     */
    QString yellow5() const;
    /**
     * @short Color yellow4
     *
     * This method returns the color code for yellow4.
     *
     * @return the color code for yellow4
     */
    QString yellow4() const;
    /**
     * @short Color yellow3
     *
     * This method returns the color code for yellow3.
     *
     * @return the color code for yellow3
     */
    QString yellow3() const;
    /**
     * @short Color yellow2
     *
     * This method returns the color code for yellow2.
     *
     * @return the color code for yellow2
     */
    QString yellow2() const;
    /**
     * @short Color yellow1
     *
     * This method returns the color code for yellow1.
     *
     * @return the color code for yellow1
     */
    QString yellow1() const;
    /**
     * @short Color gray6
     *
     * This method returns the color code for gray6.
     *
     * @return the color code for gray6
     */
    QString gray6() const;
    /**
     * @short Color gray5
     *
     * This method returns the color code for gray5.
     *
     * @return the color code for gray5
     */
    QString gray5() const;
    /**
     * @short Color gray4
     *
     * This method returns the color code for gray4.
     *
     * @return the color code for gray4
     */
    QString gray4() const;
    /**
     * @short Color gray3
     *
     * This method returns the color code for gray3.
     *
     * @return the color code for gray3
     */
    QString gray3() const;
    /**
     * @short Color gray2
     *
     * This method returns the color code for gray2.
     *
     * @return the color code for gray2
     */
    QString gray2() const;
    /**
     * @short Color gray1
     *
     * This method returns the color code for gray1.
     *
     * @return the color code for gray1
     */
    QString gray1() const;
    /**
     * @short Color white
     *
     * This method returns the color code for white.
     *
     * @return the color code for white
     */
    QString white() const;
    /**
     * @short Color black
     *
     * This method returns the color code for black.
     *
     * @return the color code for black
     */
    QString black() const;
};


}
#endif // WIDGETS_OXYGENCOLORS_H
