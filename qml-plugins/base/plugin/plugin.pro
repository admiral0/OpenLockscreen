include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui sql xml declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../lib/
LIBS +=         -L ../lib/ -lwidgetsbase

HEADERS +=      widgets_plugin.h \
                gridmanager.h \
#                widgetsviewpagemodel.h \

SOURCES +=      widgets_plugin.cpp \
                gridmanager.cpp \
#                widgetsviewpagemodel.cpp \

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \
                WidgetsView.qml \

include(deployment.pri)

