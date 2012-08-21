TEMPLATE =      lib

TARGET =        widgetsproviderbasicmixed
QT +=           declarative
CONFIG +=       qt plugin

INCLUDEPATH += ../../../../lib/base/
INCLUDEPATH += ../../../../lib/docks/
LIBS += -L../../../../lib/base/ -lwidgetsbase
LIBS += -L../../../../lib/docks/ -lwidgetsdocks

HEADERS +=      widgets_provider_basic_mixed_plugin.h \
                basicmixedprovider.h

SOURCES +=      widgets_provider_basic_mixed_plugin.cpp \
                basicmixedprovider.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)

