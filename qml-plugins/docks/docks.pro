TEMPLATE =      lib

TARGET =        widgetsdocks
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../base/lib/
LIBS +=         -L ../base/lib/ -lwidgetsbase

HEADERS +=      widgets_docks_plugin.h \
                dockmodel.h \
                dockmanager.h \

SOURCES +=      widgets_docks_plugin.cpp \
                dockmodel.cpp \
                dockmanager.cpp \

OTHER_FILES =   qmldir \
                DockContainer.qml \
                DockedView.qml \
                EmptyDockedView.qml \

include(deployment.pri)
