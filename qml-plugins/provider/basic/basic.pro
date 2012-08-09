TEMPLATE =      lib

TARGET =        widgetsproviderbasic
QT +=           declarative
CONFIG +=       qt plugin

INCLUDEPATH += ../../../qml-plugins/base/lib/
LIBS += -L../../../qml-plugins/base/lib/ -lwidgetsbase

HEADERS +=      widgets_provider_basic_plugin.h \
                basicprovider.h

SOURCES +=      widgets_provider_basic_plugin.cpp \
                basicprovider.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)

