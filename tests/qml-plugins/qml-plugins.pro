QT += xml sql
CONFIG  += qtestlib
INCLUDEPATH += ../../qml-plugins/base/lib/
INCLUDEPATH += ../../qml-plugins/docks/

LIBS += -L../../qml-plugins/base/lib/ -lwidgetsbase
LIBS += -L../../qml-plugins/docks -lwidgetsdocks

HEADERS +=  testversion.h \
            testtools.h \
            testgraphicalcomponentbase.h \
            testwidgetproperties.h \
    testdockproperties.h

SOURCES +=  main.cpp \
            testversion.cpp \
            testtools.cpp \
            testgraphicalcomponentbase.cpp \
            testwidgetproperties.cpp \
    testdockproperties.cpp

include(deployment.pri)
