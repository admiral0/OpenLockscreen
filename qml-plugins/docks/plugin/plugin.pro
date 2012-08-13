TEMPLATE =      lib

TARGET =        widgetsdocks
QT =            core gui xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../base/lib/
INCLUDEPATH +=  ../lib/
LIBS +=         -L../../base/lib/ -lwidgetsbase
LIBS +=         -L../lib/ -lwidgetsdocks

HEADERS +=      widgets_docks_plugin.h \

SOURCES +=      widgets_docks_plugin.cpp \

OTHER_FILES =   qmldir \
                Dock.qml \
                DockContainer.qml \
                DockedView.qml \
                EmptyDockedView.qml \

include(deployment.pri)

