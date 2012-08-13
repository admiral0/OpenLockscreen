include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = widgetsdocks
QT = core gui xml
INCLUDEPATH +=  ../../base/lib/
LIBS += -L../../base/lib/ -lwidgetsbase

contains(MEEGO_EDITION,harmattan):CONFIG += meegotouch

HEADERS +=      contextdocks_p.h \
                dockbaseproperties.h \
                dockbaseproperties_p.h \
                dockproperties.h \
                dockproperties_p.h \
                dockmodel.h \
                dockedviewmanager.h \
                mixedproviderbase.h \

SOURCES +=      contextdocks_p.cpp \
                dockbaseproperties.cpp \
                dockproperties.cpp \
                dockmodel.cpp \
                dockedviewmanager.cpp \
                mixedproviderbase.cpp \

include(deployment.pri)
