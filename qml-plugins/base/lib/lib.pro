include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = widgetsbase
QT = core gui sql xml

contains(MEEGO_EDITION,harmattan):CONFIG += meegotouch

HEADERS +=      widgets_global.h \
                tools.h \
                version.h \
                identifiedelementinterface.h \
                xmlserializableinterface.h \
                abstractsettings_p.h \
                settings.h \
                settingsentry.h \
                componentbase.h \
                componentbase_p.h \
                graphicalcomponentbase.h \
                graphicalcomponentbase_p.h \
                graphicalcomponentbasedefines.h \
                graphicalcomponent_p.h \
                dockbaseproperties.h \
                dockbaseproperties_p.h \
                dockproperties.h \
                desktopparser.h \
                desktopparserdefines.h \
                package.h \
                packagemanager.h \
                packagemanager_p.h \
                filterconditionlist.h \
                filtercondition.h \
                packagemanagerdefines.h \
                packagemanagerupdaterunnable.h \
                widgetbaseproperties.h \
                widgetbaseproperties_p.h \
                widgetproperties.h \
                gridmanager.h \
                widgetspagemodel.h \
                widgetspagelistmodel.h \
                configurationmanager.h

SOURCES +=      version.cpp \
                identifiedelementinterface.cpp \
                settings.cpp \
                abstractsettings_p.cpp \
                settingsentry.cpp \
                componentbase.cpp \
                graphicalcomponentbase.cpp \
                graphicalcomponentbase_p.cpp \
                dockbaseproperties.cpp \
                dockbaseproperties_p.cpp \
                dockproperties.cpp \
                desktopparser.cpp \
                package.cpp \
                packagemanager.cpp \
                packagemanager_p.cpp \
                filterconditionlist.cpp \
                filtercondition.cpp \
                packagemanagerupdaterunnable.cpp \
                widgetbaseproperties.cpp \
                widgetbaseproperties_p.cpp \
                widgetproperties.cpp \
                gridmanager.cpp \
                widgetspagemodel.cpp \
                widgetspagelistmodel.cpp \
                configurationmanager.cpp

include(deployment.pri)
