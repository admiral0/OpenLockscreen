TEMPLATE =      lib

TARGET =        widgetsinfopkgm
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../../lib/base/
INCLUDEPATH +=  ../../../lib/docks/
INCLUDEPATH +=  ../../../lib/packagemanager/
LIBS +=         -L../../../lib/base/ -lwidgetsbase
LIBS +=         -L../../../lib/docks/ -lwidgetsdocks
LIBS +=         -L../../../lib/packagemanager/ -lwidgetspackagemanager

HEADERS +=      widgets_info_packagemanager_plugin.h \
                packageinformationmodel.h \

SOURCES +=      widgets_info_packagemanager_plugin.cpp \
                packageinformationmodel.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)
