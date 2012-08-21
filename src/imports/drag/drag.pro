TEMPLATE =      lib

TARGET =        widgetsdrag
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../lib/base/
LIBS +=         -L ../../lib/base -lwidgetsbase


HEADERS +=      widgets_drag_plugin.h \
                contextdrag_p.h \
                dragmanager.h \
                draggermanager.h \
                dragparameters.h \

SOURCES +=      widgets_drag_plugin.cpp \
                contextdrag_p.cpp \
                dragmanager.cpp \
                draggermanager.cpp \
                dragparameters.cpp \

OTHER_FILES =   qmldir \
                DragOverlay.qml \
                WidgetDragger.qml \
                WidgetDraggerButton.qml \

include(deployment.pri)

