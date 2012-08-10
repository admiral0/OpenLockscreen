TEMPLATE =      lib

TARGET =        widgetsextradock
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../base/lib/
INCLUDEPATH +=  ../../docks/lib/
LIBS +=         -L../../base/lib/ -lwidgetsbase
LIBS +=         -L../../docks/lib/ -lwidgetsdocks

HEADERS +=      widget_extra_dock_plugin.h \
                dockinformationmodel.h \

SOURCES +=      widget_extra_dock_plugin.cpp \
                dockinformationmodel.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)
