TEMPLATE =      lib

TARGET =        widgetsproviderbasic
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_provider_basic_plugin.h \

SOURCES +=      widgets_provider_basic_plugin.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)

