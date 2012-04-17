include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = widgetsbase
QT = core gui sql xml

HEADERS +=      debug.h \
                version.h \
                oxygencolors.h \
                identifiedelementinterface.h \
                xmlserializableinterface.h \
                settings.h \
                settingsentry.h \
                graphicalelementbaseproperties.h \
                graphicalelementbaseproperties_p.h \
                graphicalelementbasepropertiesdefines.h \
                graphicalelementproperties_p.h \
                dockbaseproperties.h \
                dockbaseproperties_p.h \
                dockbasepropertiesdefines.h \
                dockproperties.h \
                dockproperties_p.h \
                dockpropertiesdefines.h \
                desktopparser.h \
                desktopparserdefines.h \
                package.h \
                packagemanager.h \
                packagemanager_p.h \
                packagemanagerdefines.h \
                packagemanagerupdaterunnable.h \

SOURCES +=      version.cpp \
                oxygencolors.cpp \
                identifiedelementinterface.cpp \
                settings.cpp \
                settingsentry.cpp \
                graphicalelementbaseproperties.cpp \
                dockbaseproperties.cpp \
                dockproperties.cpp \
                desktopparser.cpp \
                package.cpp \
                packagemanager.cpp \
                packagemanager_p.cpp \
                packagemanagerupdaterunnable.cpp \

include(deployment.pri)
