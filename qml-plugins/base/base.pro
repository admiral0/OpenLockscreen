include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui sql xml declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_plugin.h \
                oxygencolors.h \
                settings.h \
                settingsentry.h \
                gridmanager.h \
                identifiedelementinterface.h \
#                mainviewmodel.h \
    packagemanager.h \
    xmlserializableinterface.h \
    graphicalelementbaseproperties.h \
    graphicalelementbaseproperties_p.h \
    graphicalelementbasepropertiesdefines.h

SOURCES +=      widgets_plugin.cpp \
                oxygencolors.cpp \
                settings.cpp \
                settingsentry.cpp \
                gridmanager.cpp \
                identifiedelementinterface.cpp \
#                mainviewmodel.cpp \
    packagemanager.cpp \
    graphicalelementbaseproperties.cpp

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \
    DockedView.qml \
    DockContainer.qml

include(deployment.pri)
