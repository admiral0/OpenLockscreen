include(../../globals.pri)

TEMPLATE =      lib

TARGET =        widgetsbase
QT =            core gui sql xml declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_plugin.h \
                version.h \
                oxygencolors.h \
                settings.h \
                settingsentry.h \
                identifiedelementinterface.h \
                xmlserializableinterface.h \
                graphicalelementbaseproperties.h \
                graphicalelementbaseproperties_p.h \
                graphicalelementbasepropertiesdefines.h \
                dockbaseproperties.h \
                dockbaseproperties_p.h \
                dockbasepropertiesdefines.h \
                graphicalelementproperties_p.h \
                dockproperties.h \
                dockproperties_p.h \
                dockpropertiesdefines.h \
                desktopparserbase.h \
                gridmanager.h \
#                mainviewmodel.h \
                packagemanager.h \
    desktopparserpackage.h \
    desktopparserbase_p.h \
    desktopparserdefines.h \
    packagemanagerupdaterunnable.h

SOURCES +=      widgets_plugin.cpp \
                version.cpp \
                oxygencolors.cpp \
                settings.cpp \
                settingsentry.cpp \
                identifiedelementinterface.cpp \
                graphicalelementbaseproperties.cpp \
                dockbaseproperties.cpp \
                dockproperties.cpp \
                desktopparserbase.cpp \
                gridmanager.cpp \
#                mainviewmodel.cpp \
                packagemanager.cpp \
    desktopparserpackage.cpp \
    packagemanagerupdaterunnable.cpp

OTHER_FILES =   qmldir \
                Widget.qml \
                Dock.qml \
    DockedView.qml \
    DockContainer.qml

include(deployment.pri)
