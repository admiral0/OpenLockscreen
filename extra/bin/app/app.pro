include(../../../globals.pri)

TEMPLATE =          app
TARGET =            $${NAME}

QT =                core gui declarative xml dbus
CONFIG +=           qdeclarative-boostable

DEFINES +=          'MAIN_QML_PATH=\'\"$${QML_FOLDER}/main.qml\"\''
DEFINES +=          'BACKGROUND_FOLDER=\'\"$${DATA_FOLDER}/\"\''
CONFIG(noqtimport):DEFINES += 'IMPORT_DIR=\'\"$${IMPORTDIR}\"\''

HEADERS +=          webandmailhandler.h \
                    remotesettingsmanager.h \
                    imagesupport.h

SOURCES +=          main.cpp \
                    webandmailhandler.cpp \
                    remotesettingsmanager.cpp \
                    imagesupport.cpp

QML_FILES +=        qml/main.qml \
                    qml/UiConstants.js \
                    qml/HorizontalSeparator.qml \
                    qml/ClickableEntry.qml \
                    qml/CheckableEntry.qml \
                    qml/Background.qml \
                    qml/AbstractPage.qml \
                    qml/AbstractNavigationPage.qml \
                    qml/MainPage.qml \
                    qml/PreviewPage.qml \
                    qml/WidgetsPage.qml \
                    qml/SettingsPage.qml \
                    qml/DockEditorPage.qml \
                    qml/WidgetEditorPage.qml \
                    qml/WidgetEditorSelectorSheet.qml \
                    qml/BackgroundEditorPage.qml \
                    qml/InformationsPage.qml \
                    qml/PackageListPage.qml \
                    qml/PackageDetailPage.qml \
                    qml/DockListPage.qml \
                    qml/WidgetListPage.qml \
                    qml/AboutPage.qml \

DATA_FILES +=       data/wallpaper-1.png \
                    data/wallpaper-2.png \
                    data/wallpaper-3.png \
                    data/wallpaper-4.png \
                    data/wallpaper-1-thumbnail.png \
                    data/wallpaper-2-thumbnail.png \
                    data/wallpaper-3-thumbnail.png \
                    data/wallpaper-4-thumbnail.png \



include(deployment.pri)
