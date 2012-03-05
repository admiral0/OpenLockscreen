include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsextension
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_plugin.h \

SOURCES +=      widgets_plugin.cpp \

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \

include(deployment.pri)
