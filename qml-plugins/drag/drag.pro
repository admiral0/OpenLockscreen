include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsdrag
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../base/lib/
LIBS +=         -L ../base/lib/ -lwidgetsbase


HEADERS +=      widgets_drag_plugin.h \
    dragmanager.h

SOURCES +=      widgets_drag_plugin.cpp \
    dragmanager.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)

