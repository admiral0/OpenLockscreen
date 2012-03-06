include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbackground
QT +=           declarative
CONFIG +=       qt plugin
INCLUDEPATH +=  ../base/

HEADERS +=      widgets_background_plugin.h \
                backgroundmanager.h \
                ../base/settings.h \

SOURCES +=      widgets_background_plugin.cpp \
                backgroundmanager.cpp \
                ../base/settings.cpp \

OTHER_FILES =   qmldir \
                HorizontalParallaxBackground.qml \

include(deployment.pri)
