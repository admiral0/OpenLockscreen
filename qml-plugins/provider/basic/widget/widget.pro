TEMPLATE =      lib

TARGET =        widgetsproviderbasicwidget
QT +=           declarative
CONFIG +=       qt plugin

INCLUDEPATH += ../../../../qml-plugins/base/lib/
LIBS += -L../../../../qml-plugins/base/lib/ -lwidgetsbase

HEADERS +=      widgets_provider_basic_widget_plugin.h \
                basicwidgetprovider.h

SOURCES +=      widgets_provider_basic_widget_plugin.cpp \
                basicwidgetprovider.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)

