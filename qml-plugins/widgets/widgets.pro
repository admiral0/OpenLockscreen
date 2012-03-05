include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgets
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_plugin.h \
                oxygencolors.h

SOURCES +=      widgets_plugin.cpp \
                oxygencolors.cpp

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \

include(deployment.pri)
