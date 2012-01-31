include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsextension
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_plugin.h \
                selectormodel.h \

SOURCES +=      widgets_plugin.cpp \
                selectormodel.cpp \

OTHER_FILES =   qmldir \
                UiConstants.js \
                Widget.qml \
                Dock.qml \
                ClickableEntry.qml \
                GroupIndicator.qml \
                HorizontalSeparator.qml \

include(deployment.pri)
