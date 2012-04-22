include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsextra
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../base/lib/
LIBS +=         -L ../base/lib/ -lwidgetsbase

HEADERS +=      widgets_extra_plugin.h \
                packageinformationmodel.h \
                dockinformationmodel.h

SOURCES +=      widgets_extra_plugin.cpp \
                packageinformationmodel.cpp \
                dockinformationmodel.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)
