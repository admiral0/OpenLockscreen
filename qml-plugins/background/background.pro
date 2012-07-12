TEMPLATE =      lib

TARGET =        widgetsbackground
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../base/lib/
LIBS +=         -L ../base/lib/ -lwidgetsbase


HEADERS +=      widgets_background_plugin.h \
                backgroundmanager.h \

SOURCES +=      widgets_background_plugin.cpp \
                backgroundmanager.cpp \

OTHER_FILES =   qmldir \
                HorizontalParallaxBackground.qml \

include(deployment.pri)
