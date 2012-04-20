include(../globals.pri)

TEMPLATE =          app
TARGET =            widgets

QT =                core gui declarative xml
CONFIG +=           qdeclarative-boostable
#INCLUDEPATH += ../widgetsdev/widgetsapi/

DEFINES +=          'MAIN_QML_PATH=\'\"$${DEPLOYMENT_PREFIX}/$${APPLICATION_FOLDER}/qml/main.qml\"\''

SOURCES +=          main.cpp \
    webandmailhandler.cpp

QML_FILES +=        qml/main.qml \
                    qml/UiConstants.js \
                    qml/HorizontalSeparator.qml \
                    qml/ClickableEntry.qml \
                    qml/AbstractPage.qml \
                    qml/AbstractNavigationPage.qml \
                    qml/MainPage.qml \
                    qml/InformationsPage.qml \
                    qml/PackageListPage.qml \
                    qml/PackageDetailPage.qml \
                    qml/DockListPage.qml \
                    qml/AboutPage.qml \



DATA_FILES +=       data/wallpaper-1.jpg \


include(deployment.pri)

HEADERS += \
    webandmailhandler.h
