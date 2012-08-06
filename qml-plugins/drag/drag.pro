TEMPLATE =      lib

TARGET =        widgetsdrag
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../base/lib/
LIBS +=         -L ../base/lib/ -lwidgetsbase


HEADERS +=      widgets_drag_plugin.h \
                dragmanager.h \
    draggermanager.h

SOURCES +=      widgets_drag_plugin.cpp \
                dragmanager.cpp \
    draggermanager.cpp

OTHER_FILES =   qmldir \
                DragOverlay.qml \
                WidgetDragger.qml \

include(deployment.pri)

