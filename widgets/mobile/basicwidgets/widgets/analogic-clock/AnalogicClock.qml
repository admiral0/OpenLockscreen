/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 1.1
import org.SfietKonstantin.widgets 1.0
import QtMobility.systeminfo 1.2

Widget {
    id: clock

    property int hours
    property int minutes
    property bool night: false
    property string dayBackgroundSource: "analogic-clock-background.png"
    property string nightBackgroundSource: "analogic-clock-night-background.png"
    onEnabledChanged: {
        enabled ? timer.start() : timer.stop()
        if (enabled) {
            changeTime()
        }
    }

    Component.onCompleted: changeTime()
    function changeTime() {
        var date = new Date
        hours = date.getHours()
        night = ( hours < 7 || hours > 19 )
        minutes = date.getMinutes()
    }
    width: 200
    height: 200

    AlignedTimer {
        id: timer
        minimumInterval: 1
        maximumInterval: 1
        singleShot: false
        onTimeout: clock.changeTime()
        Component.onCompleted: start()
    }

    Image {
        id: background
        source: !clock.night ? dayBackgroundSource : nightBackgroundSource
    }

    Image {
        x: 92.5; y: 27
        source: "analogic-clock-hour.png"
        smooth: true
        transform: Rotation {
            id: hourRotation
            origin.x: 7.5; origin.y: 73;
            angle: (clock.hours * 30) + (clock.minutes * 0.5)
            Behavior on angle {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }

    Image {
        x: 93.5; y: 17
        source: "analogic-clock-minute.png"
        smooth: true
        transform: Rotation {
            id: minuteRotation
            origin.x: 6.5; origin.y: 83;
            angle: clock.minutes * 6
            Behavior on angle {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
        }
    }

    Image {
        anchors.centerIn: background; source: "analogic-clock-center.png"
    }

    Text {
        id: cityLabel
        y: 200; anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
        font.bold: true; font.pixelSize: 14
        style: Text.Raised; styleColor: "black"
    }
}
