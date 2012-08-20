TEMPLATE =      lib

TARGET =        widgetsinfodock
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../base/lib/
INCLUDEPATH +=  ../../docks/lib/
LIBS +=         -L../../base/lib/ -lwidgetsbase
LIBS +=         -L../../docks/lib/ -lwidgetsdocks

HEADERS +=      widgets_info_dock_plugin.h \
                dockinformationmodel.h \

SOURCES +=      widgets_info_dock_plugin.cpp \
                dockinformationmodel.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)
