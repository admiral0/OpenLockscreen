TEMPLATE =      lib

TARGET =        widgetsextrapackagemanager
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../base/lib/
INCLUDEPATH +=  ../../docks/lib/
INCLUDEPATH +=  ../../provider/packagemanager/lib/
LIBS +=         -L../../base/lib/ -lwidgetsbase
LIBS +=         -L../../docks/lib/ -lwidgetsdocks
LIBS +=         -L../../provider/packagemanager/lib/ -lwidgetspackagemanagerprovider

HEADERS +=      widgets_extra_packagemanager_plugin.h \
                packageinformationmodel.h \

SOURCES +=      widgets_extra_packagemanager_plugin.cpp \
                packageinformationmodel.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)
