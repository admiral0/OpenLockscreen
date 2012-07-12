QT += sql
CONFIG  += qtestlib
LIBS +=     ../../../qml-plugins/base/lib/


HEADERS +=  test.h \
            ../../../qml-plugins/base/version.h \
            ../../../qml-plugins/base/package.h \
            ../../../qml-plugins/base/desktopparser.h \
            ../../../qml-plugins/base/packagemanager.h \
            ../../../qml-plugins/base/packagemanager_p.h \
            temporarypackagemanager.h

SOURCES += test.cpp \
            ../../../qml-plugins/base/version.cpp \
            ../../../qml-plugins/base/desktopparser.cpp \
            ../../../qml-plugins/base/package.cpp \
            ../../../qml-plugins/base/packagemanager.cpp \
            ../../../qml-plugins/base/packagemanager_p.cpp \
            temporarypackagemanager.cpp

include(deployment.pri)
