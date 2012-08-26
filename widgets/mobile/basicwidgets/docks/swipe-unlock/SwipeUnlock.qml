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

import QtQuick 1.1
import org.SfietKonstantin.widgets.docks 1.0
import org.SfietKonstantin.widgets.colors 1.0
import org.SfietKonstantin.mobile.launcher 1.0

Dock {
    id: container
    height: 100
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right

    Rectangle {
        id: backgroundShadow
        anchors.bottom: background.top
        anchors.left: background.left
        anchors.right: background.right
        height: 4
        opacity: 0.5
        color: Colors.black
    }
    Rectangle {
        id: background
        anchors.top: parent.top
        anchors.bottom: parent.bottom; anchors.bottomMargin: -2
        anchors.left: parent.left; anchors.leftMargin: -2
        anchors.right: parent.right; anchors.rightMargin: -2

        gradient: Gradient {
            GradientStop {position: 0; color: Colors.aluminiumGray6}
            GradientStop {position: 1; color: Colors.black}
        }
        border.color: Colors.aluminiumGray3
        border.width: 2

        Rectangle {
            smooth: true
            height: background.height - 30
            width: background.width - 100
            radius: 14
            anchors.centerIn: parent

            gradient: Gradient {
                GradientStop {position: 0; color: Colors.black}
                GradientStop {position: 1; color: Colors.aluminiumGray6}
            }
            border.color: Colors.black
            border.width: 2

            Item {
                id: sliderRail
                anchors.left: parent.left; anchors.leftMargin: 10
                anchors.right: parent.right; anchors.rightMargin: 10
                anchors.top: parent.top; anchors.bottom: parent.bottom

                Text {
                    anchors.centerIn: parent; anchors.horizontalCenterOffset: 45
                    text: qsTr("Swipe to unlock")
                    color: Colors.white
                    font.pixelSize: 30
                    opacity: Math.max(1 - 2 * (slider.x) / (sliderRail.width - slider.width), 0)
                }

                Rectangle {
                    id: slider
                    anchors.verticalCenter: parent.verticalCenter
                    width: 90
                    height: sliderRail.height - 20
                    radius: 14
                    smooth: true
                    gradient: Gradient {
                        GradientStop {position: 0; color: Colors.aluminiumGray2}
                        GradientStop {position: 1; color: Colors.aluminiumGray5}
                    }

                    Image {
                        height: 35
                        width: 50
                        source: "arrow.png"
                        anchors.centerIn: parent
                        smooth: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        anchors.margins: -10
                        drag.target: slider
                        drag.axis: Drag.XAxis
                        drag.minimumX: 0
                        drag.maximumX: sliderRail.width - slider.width
                        onReleased: {
                            if (slider.x == sliderRail.width - slider.width) {
                                LauncherManagerInstance.unlock()
                            }
                            slider.x = 0
                        }
                    }

                    Behavior on x {
                        NumberAnimation {easing.type: Easing.OutQuad; duration: 200}
                    }
                }
            }
        }
    }
}
