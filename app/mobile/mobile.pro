include(../../globals.pri)

TEMPLATE =          app
TARGET =            widgets

QT =                core gui declarative xml dbus
CONFIG +=           qdeclarative-boostable

DEFINES +=          'MAIN_QML_PATH=\'\"$${QML_FOLDER}/main.qml\"\''
CONFIG(noqtimport):DEFINES += 'IMPORT_DIR=\'\"$${IMPORTDIR}\"\''

HEADERS +=          webandmailhandler.h \
                    remotesettingsmanager.h

SOURCES +=          main.cpp \
                    webandmailhandler.cpp \
                    remotesettingsmanager.cpp

QML_FILES +=        qml/main.qml \
                    qml/UiConstants.js \
                    qml/HorizontalSeparator.qml \
                    qml/ClickableEntry.qml \
                    qml/CheckableEntry.qml \
                    qml/AbstractPage.qml \
                    qml/AbstractNavigationPage.qml \
                    qml/MainPage.qml \
                    qml/PreviewPage.qml \
                    qml/WidgetsPage.qml \
                    qml/SettingsPage.qml \
                    qml/DockEditorPage.qml \
                    qml/WidgetEditorPage.qml \
                    qml/WidgetEditorSelectorSheet.qml \
                    qml/Background.qml \
                    qml/InformationsPage.qml \
                    qml/PackageListPage.qml \
                    qml/PackageDetailPage.qml \
                    qml/DockListPage.qml \
                    qml/WidgetListPage.qml \
                    qml/AboutPage.qml \

DATA_FILES +=       data/wallpaper-1.png \


include(deployment.pri)
