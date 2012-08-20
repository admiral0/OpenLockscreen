TEMPLATE =      lib

TARGET =        widgetsinfowidget
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../base/lib/
LIBS +=         -L ../../base/lib/ -lwidgetsbase

HEADERS +=      widgets_info_widget_plugin.h \
                widgetinformationmodel.h

SOURCES +=      widgets_info_widget_plugin.cpp \
                widgetinformationmodel.cpp

OTHER_FILES =   qmldir \

include(deployment.pri)
