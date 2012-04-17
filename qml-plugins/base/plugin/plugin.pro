include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui sql xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../lib/
LIBS +=         -L ../lib/ -lwidgetsbase

HEADERS +=      widgets_plugin.h \
                gridmanager.h \
#                mainviewmodel.h \

SOURCES +=      widgets_plugin.cpp \
                gridmanager.cpp \
#                mainviewmodel.cpp \

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \
                DockContainer.qml \
                DockedView.qml \

include(deployment.pri)

