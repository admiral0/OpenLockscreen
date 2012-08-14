TEMPLATE =      lib

TARGET =        widgetsproviderpackagemanager
QT +=           core gui sql declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../lib/
INCLUDEPATH +=  ../../../base/lib
INCLUDEPATH += ../../../docks/lib
LIBS += -L../../../base/lib/ -lwidgetsbase
LIBS += -L../../../docks/lib/ -lwidgetsdocks
LIBS += -L ../lib/ -lwidgetspackagemanagerprovider

HEADERS +=      widgets_provider_packagemanager_plugin.h \

SOURCES +=      widgets_provider_packagemanager_plugin.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)

