TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../lib/base/
LIBS +=         -L ../../lib/base/ -lwidgetsbase

HEADERS +=      widgets_plugin.h \

SOURCES +=      widgets_plugin.cpp \

OTHER_FILES =   qmldir \
                Widget.qml \
                SettingsItem.qml \
                WidgetContainer.qml \
                WidgestPage.qml \
                WidgetsView.qml \
                WidgetsHorizontalPageView.qml \

include(deployment.pri)

