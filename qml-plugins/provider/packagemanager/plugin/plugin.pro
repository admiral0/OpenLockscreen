TEMPLATE =      lib

TARGET =        widgetsproviderpackagemanager
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_provider_packagemanager_plugin.h \

SOURCES +=      widgets_provider_packagemanager_plugin.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)

