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
import com.nokia.meego 1.0
import com.nokia.extras 1.1
//import QtMobility.gallery 1.1
import org.SfietKonstantin.widgets.app 1.0

AbstractPage {
    id: container
    property int wallpaperWidth: widgetsSettings.value("background", "wallpaperWidth")
    property int wallpaperHeight:widgetsSettings.value("background", "wallpaperHeight")
    property string selected: widgetsSettings.value("background", "wallpaperSource")
    signal backgroundChanged()

    title: qsTr("Edit background")
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                widgetsSettings.setValue("background", "wallpaperSource", container.selected)
                widgetsSettings.setValue("background", "wallpaperWidth", container.wallpaperWidth)
                widgetsSettings.setValue("background", "wallpaperHeight", container.wallpaperHeight)
                window.pageStack.pop()
                container.backgroundChanged()
            }
        }

        ButtonRow {
            TabButton {
                text: qsTr("Preloaded")
                onClicked: {
                    preloaded.visible = true
                    images.visible = false
                }
            }
            TabButton {
                text: qsTr("Images")
                onClicked: {
                    preloaded.visible = false
                    images.visible = true
                }
            }
        }
    }
    content: Item {
        anchors.fill: parent

        InfoBanner {
            id: infobanner
            text: qsTr("The image is a portrait image and is not supported for the background")
        }

        Item {
            id: preloaded
            anchors.fill: parent
            GridView {
                width: container.width
                height: container.height - 70
                clip: true
                model: preloadedModel
                cellHeight: 160
                cellWidth: 160

                delegate: Item {
                    height: 160
                    width: 160
                    property bool selected: container.selected == (BACKGROUND_FOLDER + model.source)

                    Rectangle {
                        id: preloadedSelectedRectangle
                        anchors.fill: parent
                        visible: false
                        color: "#6193CF"
                    }

                    Image {
                        id: preloadedImage
                        width: parent.width; height: parent.height
                        anchors.centerIn: parent
                        asynchronous: true
                        smooth: true
                        source: BACKGROUND_FOLDER + model.thumbSource
                    }

                    states: State {
                        name: "selected"; when: selected
                        PropertyChanges {
                            target: preloadedSelectedRectangle
                            visible: true
                        }
                        PropertyChanges {
                            target: preloadedImage
                            scale: 0.95
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            container.selected = (BACKGROUND_FOLDER + model.source)
                            container.wallpaperWidth = 1440
                            container.wallpaperHeight = 900
                        }
                    }
                }
            }

            ListModel {
                id: preloadedModel
                ListElement {
                    thumbSource: "wallpaper-1-thumbnail.png"
                    source: "wallpaper-1.png"
                }
                ListElement {
                    thumbSource: "wallpaper-2-thumbnail.png"
                    source: "wallpaper-2.png"
                }
                ListElement {
                    thumbSource: "wallpaper-3-thumbnail.png"
                    source: "wallpaper-3.png"
                }
                ListElement {
                    thumbSource: "wallpaper-4-thumbnail.png"
                    source: "wallpaper-4.png"
                }
            }
        }

        Item {
            id: images
            visible: false
            anchors.fill: parent

            ImageSupport {
                id: imageSupport
            }

            GridView {
                width: container.width
                height: container.height - 70
                clip: true
//                model: imagesModel
                cellHeight: 160
                cellWidth: 160
                delegate: Item {
                    height: 160
                    width: 160
                    property bool selected: container.selected == model.url

                    Rectangle {
                        id: imagesSelectedRectangle
                        anchors.fill: parent
                        visible: false
                        color: "#6193CF"
                    }

                    Image {
                        id: imagesImage
                        width: parent.width; height: parent.height
                        anchors.centerIn: parent
                        asynchronous: true
                        smooth: true
                        source: "file:///home/user/.thumbnails/grid/" + Qt.md5(model.url) + ".jpeg"
                    }

                    states: State {
                        name: "selected"; when: selected
                        PropertyChanges {
                            target: imagesSelectedRectangle
                            visible: true
                        }
                        PropertyChanges {
                            target: imagesImage
                            scale: 0.95
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            var size = imageSupport.imageSize(model.url)
                            if (size.width < size.height) {
                                infobanner.show()
                                return
                            }

                            container.selected = model.url
                            container.wallpaperWidth = size.width
                            container.wallpaperHeight = size.height
                        }
                    }
                }
            }
            /*DocumentGalleryModel {
                id: imagesModel
                rootType: DocumentGallery.Image
                properties: ["url"]
                filter: GalleryFilterUnion {
                    filters: [
                        GalleryWildcardFilter {
                            property: "fileName"
                            value: "*.jpg"
                        },
                        GalleryWildcardFilter {
                            property: "fileName"
                            value: "*.png"
                        }
                    ]
                }
            }*/
        }
    }
}
