include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui sql xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../lib/
LIBS +=         -L ../lib/ -lwidgetsbase

HEADERS +=      widgets_plugin.h \
                gridmanager.h \

SOURCES +=      widgets_plugin.cpp \
                gridmanager.cpp \

OTHER_FILES =   qmldir \
                WidgetManager.qml \
                Widget.qml \
                Dock.qml \

include(deployment.pri)
