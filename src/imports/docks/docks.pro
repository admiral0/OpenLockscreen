TEMPLATE =      lib

TARGET =        widgetsdocks
QT =            core gui xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../lib/base/
INCLUDEPATH +=  ../../lib/docks/
LIBS +=         -L../../lib/base/ -lwidgetsbase
LIBS +=         -L../../lib/docks/ -lwidgetsdocks

HEADERS +=      widgets_docks_plugin.h \

SOURCES +=      widgets_docks_plugin.cpp \

OTHER_FILES =   qmldir \
                Dock.qml \
                DockContainer.qml \
                DockedView.qml \
                EmptyDockedView.qml \

include(deployment.pri)

