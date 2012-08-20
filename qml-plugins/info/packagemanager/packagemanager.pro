TEMPLATE =      lib

TARGET =        widgetsinfopkgm
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../base/lib/
INCLUDEPATH +=  ../../docks/lib/
INCLUDEPATH +=  ../../provider/packagemanager/lib/
LIBS +=         -L../../base/lib/ -lwidgetsbase
LIBS +=         -L../../docks/lib/ -lwidgetsdocks
LIBS +=         -L../../provider/packagemanager/lib/ -lwidgetsproviderpackagemanager

HEADERS +=      widgets_info_packagemanager_plugin.h \
                packageinformationmodel.h \

SOURCES +=      widgets_info_packagemanager_plugin.cpp \
                packageinformationmodel.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)
