include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui sql xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../lib/
LIBS +=         -L ../lib/ -lwidgetsbase

HEADERS +=      widgets_plugin.h \
                gridmanager.h \
                widgetspagemodel.h \
                widgetspagelistmodel.h \

SOURCES +=      widgets_plugin.cpp \
                gridmanager.cpp \
                widgetspagemodel.cpp \
                widgetspagelistmodel.cpp \

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \
                WidgestPage.qml \
                WidgetsView.qml \
                WidgetsHorizontalPageView.qml \

include(deployment.pri)

