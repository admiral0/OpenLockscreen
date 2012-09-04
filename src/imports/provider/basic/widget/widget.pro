TEMPLATE =      lib

TARGET =        providerbasicwidgetplugin
QT +=           declarative
CONFIG +=       qt plugin

INCLUDEPATH += ../../../../lib/base/
LIBS += -L../../../../lib/base/ -lwidgetsbase

HEADERS +=      widgets_provider_basic_widget_plugin.h \
                basicwidgetprovider.h

SOURCES +=      widgets_provider_basic_widget_plugin.cpp \
                basicwidgetprovider.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)

