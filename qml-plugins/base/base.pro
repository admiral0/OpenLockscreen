include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbase
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_plugin.h \
                oxygencolors.h \
                settings.h \
                gridmanager.h \
    settingsentry.h

SOURCES +=      widgets_plugin.cpp \
                oxygencolors.cpp \
                settings.cpp \
                gridmanager.cpp \
    settingsentry.cpp

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \

include(deployment.pri)
