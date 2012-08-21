TEMPLATE =      lib

TARGET =        widgetsbackground
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../../lib/base/
LIBS +=         -L ../../lib/base/ -lwidgetsbase


HEADERS +=      widgets_background_plugin.h \
                backgroundmanager.h \
                parallaxmanager.h

SOURCES +=      widgets_background_plugin.cpp \
                backgroundmanager.cpp \
                parallaxmanager.cpp

OTHER_FILES =   qmldir \
                HorizontalParallaxBackground.qml \

include(deployment.pri)
