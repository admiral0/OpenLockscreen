QT += xml sql
CONFIG  += qtestlib
INCLUDEPATH += ../../../qml-plugins/base/lib/
LIBS += -L../../../qml-plugins/base/lib/ -lwidgetsbase

HEADERS +=  testversion.h \
            testtools.h

SOURCES +=  main.cpp \
            testversion.cpp \
            testtools.cpp

include(deployment.pri)
