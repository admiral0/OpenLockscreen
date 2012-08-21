QT += xml
CONFIG  += qtestlib
INCLUDEPATH += ../../src/lib/base/
INCLUDEPATH += ../../src/lib/docks/

LIBS += -L../../src/lib/base/ -lwidgetsbase
LIBS += -L../../src/lib/docks/ -lwidgetsdocks

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
