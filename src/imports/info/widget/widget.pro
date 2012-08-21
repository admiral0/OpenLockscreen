TEMPLATE =      lib

TARGET =        widgetsinfowidget
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../../lib/base/
LIBS +=         -L../../../lib/base/ -lwidgetsbase

HEADERS +=      widgets_info_widget_plugin.h \
                widgetinformationmodel.h

SOURCES +=      widgets_info_widget_plugin.cpp \
                widgetinformationmodel.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)
