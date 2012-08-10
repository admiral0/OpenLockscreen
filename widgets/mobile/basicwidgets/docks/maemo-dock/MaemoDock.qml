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
import com.nokia.meego 1.0
import QtMobility.systeminfo 1.2

Dock {
    id: container
    width: 480
    height: 60
    anchors.top: parent.top
    anchors.left: parent.left

    onEnabledChanged: {
        if(enabled) {
            timer.start()
        } else {
            timer.stop()
        }
    }

    Rectangle {
        id: bar
        width: 280
        height: 60
        color: Colors.gray6
        opacity: 0.9
        radius: 6

        MaemoDockButton {
            id: maemoMenu
            height: container.height
            anchors.verticalCenter: parent.verticalCenter
        }

        BorderImage {
            id: separator
            anchors.left: maemoMenu.right
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height - 2 * 10; width: 2
            source: "image://theme/meegotouch-separator" + (theme.inverted ? "-inverted" : "") +
                    "-background-vertical"
            border {left: 2; top: 0; right: 0; bottom: 0}
        }

        Item {
            id: clockContainer
            anchors.left: separator.right; anchors.leftMargin: 10
            width: 100
            height: container.height
            property int hours
            property int minutes

            function changeTime() {
                var date = new Date;
                clockText.text = Qt.formatTime(date , "hh:mm")
            }

            Component.onCompleted: changeTime()

            Text {
                id: clockText
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 35
            }
        }

        Item {
            id: indicatorsContainer
            anchors.left: clockContainer.right; anchors.leftMargin: 10
            anchors.right: bar.right; anchors.rightMargin: 10
            height: container.height


            Item {
                id: antennaContainer
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left; anchors.leftMargin: 5
                height: 41
                width: 17

                Item {
                    id: antennaGraphContainer
                    width: antennaContainer.width
                    height: 5 * 3 + 4 * 2
                    transformOrigin: Item.Center
                    rotation: 180

                    Column {
                        id: antennaColum
                        spacing: 2
                        width: 13
                        anchors.horizontalCenter: parent.horizontalCenter

                        Repeater {
                            id: antennaRepeater
                            model: networkInfo.networkSignalStrength / 100 * 5
                            delegate: Rectangle {
                                width: antennaColum.width
                                height: 3
                                radius: 1
                            }
                        }
                    }
                }

                Label {
                    id: antennaTechnology
                    function technologyText(technology) {
                        if(technology == NetworkInfo.GprsDataTechnology) {
                            return "2G"
                        } else if(technology == NetworkInfo.EdgeDataTechnology) {
                            return "2.5"
                        } else if(technology == NetworkInfo.UmtsDataTechnology) {
                            return "3G"
                        } else if(technology == NetworkInfo.HspaDataTechnology) {
                            return "3.5"
                        }
                        return "?"
                    }
                    anchors.bottom: antennaContainer.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: technologyText(networkInfo.cellDataTechnology)
                    font.pixelSize: 12
                }
            }

            Item {
                id: batteryHolder
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right; anchors.rightMargin: 5
                height: 41
                width: 17
                Rectangle {
                    id: batteryTop
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 7
                    height: 3
                }

                Rectangle {
                    id: batteryBody
                    anchors.top: batteryTop.bottom
                    width: 17
                    height: 36
                    radius: 3
                    color: Colors.white

                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.width - 4
                        height: parent.height - 4
                        color: Colors.gray6

                        Rectangle {
                            id: level
                            anchors.bottom: parent.bottom; anchors.bottomMargin: 1
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width - 2
                            height: batteryInfo.remainingCapacity / batteryInfo.nominalCapacity *
                                    (parent.height - 2)
                            color: Colors.green5
                        }
                    }
                }
            }
        }
    }

    Label {
        id: networkProviderText
        anchors.left: bar.right; anchors.leftMargin: 16
        anchors.right: parent.right; anchors.rightMargin: 16
        height: container.height
        text: networkInfo.networkName
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.NoWrap
        font.pixelSize: 30
    }

    AlignedTimer {
        id: timer
        minimumInterval: 1
        maximumInterval: 1
        singleShot: false
        onTimeout: clockContainer.changeTime()

        Component.onCompleted: start()
    }

    NetworkInfo {
         id: networkInfo
         mode: NetworkInfo.WcdmaMode
         monitorNameChanges: true
         monitorSignalStrengthChanges: true
    }

    BatteryInfo {
         id: batteryInfo
    }


}
