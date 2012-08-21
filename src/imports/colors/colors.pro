TEMPLATE =      lib

TARGET =        widgetscolors
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_colors_plugin.h \
                oxygencolors.h \

SOURCES +=      widgets_colors_plugin.cpp \
                oxygencolors.cpp \

OTHER_FILES =   qmldir \

include(deployment.pri)
