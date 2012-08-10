TEMPLATE =      lib

TARGET =        widgetsproviderbasicmixed
QT +=           declarative
CONFIG +=       qt plugin

INCLUDEPATH += ../../../../qml-plugins/base/lib/
INCLUDEPATH += ../../../../qml-plugins/docks/lib/
LIBS += -L../../../../qml-plugins/base/lib/ -lwidgetsbase
LIBS += -L../../../../qml-plugins/docks/lib/ -lwidgetsdocks

HEADERS +=      widgets_provider_basic_mixed_plugin.h \
                basicmixedprovider.h

SOURCES +=      widgets_provider_basic_mixed_plugin.cpp \
                basicmixedprovider.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)

