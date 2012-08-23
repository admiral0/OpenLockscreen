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
import org.SfietKonstantin.widgets.colors 1.0
import QtMobility.systeminfo 1.2

Widget {
    id: clock
    onEnabledChanged: {
        enabled ? timer.start() : timer.stop()
    }
    Component.onCompleted: changeTime()
    function changeTime() {
        var dateTime = new Date
        time.text = Qt.formatTime(dateTime)
        date.text = Qt.formatDate(dateTime, Qt.DefaultLocaleLongDate)
    }
    width: 460
    height: 200

     AlignedTimer {
         id: timer
         minimumInterval: 1
         maximumInterval: 1
         singleShot: false
         onTimeout: clock.changeTime()
         Component.onCompleted: start()
     }

    Rectangle {
        id: background
        anchors.fill: parent
        radius: 10
        border.color: Colors.aluminiumGray5
        border.width: 3
        opacity: 0.9
        gradient: Gradient {
            GradientStop {position: 0; color: Colors.aluminiumGray6}
            GradientStop {position: 1; color: Colors.black}
        }
    }

    Item {
        width: background.width
        height: time.height + 7 + date.height
        anchors.centerIn: background

        Text {
            id: time
            anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top
            font.pixelSize: 85
            color: Colors.white
            style: Text.Outline
            styleColor: Colors.black
        }

        Text {
            id: date
            anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom
            font.pixelSize: 30
            color: Colors.white
            style: Text.Outline
            styleColor: Colors.black
        }
    }




}
