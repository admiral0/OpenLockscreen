TEMPLATE =      lib

TARGET =        infodockplugin
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../../lib/base/
INCLUDEPATH +=  ../../../lib/docks/
LIBS +=         -L../../../lib/base/ -lwidgetsbase
LIBS +=         -L../../../lib/docks/ -lwidgetsdocks

HEADERS +=      widgets_info_dock_plugin.h \
                dockinformationmodel.h \

SOURCES +=      widgets_info_dock_plugin.cpp \
                dockinformationmodel.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)
