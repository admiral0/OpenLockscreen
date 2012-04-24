include(../globals.pri)

TEMPLATE =          app
TARGET =            widgets

QT =                core gui declarative xml
CONFIG +=           qdeclarative-boostable

DEFINES +=          'MAIN_QML_PATH=\'\"$${DEPLOYMENT_PREFIX}/$${APPLICATION_FOLDER}/qml/main.qml\"\''

HEADERS +=          webandmailhandler.h \

SOURCES +=          main.cpp \
                    webandmailhandler.cpp

QML_FILES +=        qml/main.qml \
                    qml/UiConstants.js \
                    qml/HorizontalSeparator.qml \
                    qml/ClickableEntry.qml \
                    qml/CheckableEntry.qml \
                    qml/AbstractPage.qml \
                    qml/AbstractNavigationPage.qml \
                    qml/MainPage.qml \
                    qml/PreviewPage.qml \
                    qml/SettingsPage.qml \
                    qml/DockEditorPage.qml \
                    qml/Background.qml \
                    qml/InformationsPage.qml \
                    qml/PackageListPage.qml \
                    qml/PackageDetailPage.qml \
                    qml/DockListPage.qml \
                    qml/WidgetListPage.qml \
                    qml/AboutPage.qml \



DATA_FILES +=       data/wallpaper-1.jpg \


include(deployment.pri)


