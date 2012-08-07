TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui sql xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../lib/
LIBS +=         -L ../lib/ -lwidgetsbase

HEADERS +=      widgets_plugin.h \

SOURCES +=      widgets_plugin.cpp \

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \
                SettingsItem.qml \
                WidgetContainer.qml \
                WidgestPage.qml \
                WidgetsView.qml \
                WidgetsHorizontalPageView.qml \

include(deployment.pri)

