QT += xml sql
CONFIG  += qtestlib
INCLUDEPATH += ../../../qml-plugins/base/lib/
LIBS += -L../../../qml-plugins/base/lib/ -lwidgetsbase

HEADERS +=  testversion.h \
            testtools.h \
            testgraphicalcomponentbase.h \
            testwidgetproperties.h

SOURCES +=  main.cpp \
            testversion.cpp \
            testtools.cpp \
            testgraphicalcomponentbase.cpp \
            testwidgetproperties.cpp

include(deployment.pri)
