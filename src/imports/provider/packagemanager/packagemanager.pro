TEMPLATE =      lib

TARGET =        widgetsproviderpkgm
QT +=           core gui sql declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../../lib/base/
INCLUDEPATH +=  ../../../lib/docks/
INCLUDEPATH +=  ../../../lib/packagemanager/
INCLUDEPATH +=  ../../../base/lib
INCLUDEPATH += ../../../docks/lib
LIBS += -L../../../lib/base/ -lwidgetsbase
LIBS += -L../../../lib/docks/ -lwidgetsdocks
LIBS += -L../../../lib/packagemanager/ -lwidgetspackagemanager

HEADERS +=      widgets_provider_packagemanager_plugin.h \

SOURCES +=      widgets_provider_packagemanager_plugin.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)

