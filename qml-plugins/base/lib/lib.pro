include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = widgetsbase
QT = core gui xml

contains(MEEGO_EDITION,harmattan):CONFIG += meegotouch

HEADERS +=      widgets_global.h \
                contextbase_p.h \
                builderpatterninterfaces_p.h \
                tools.h \
                version.h \
                identifiedelementinterface.h \
                widgetproviderbase.h \
                widgetproviderbase_p.h \
                providermanager.h \
                abstractsettings_p.h \
                settings.h \
                settingsentry.h \
                graphicalcomponentbase_p.h \
                graphicalcomponentbase.h \
                widgetbaseproperties.h \
                widgetbaseproperties_p.h \
                widgetproperties.h \
                widgetproperties_p.h \
                gridmanager.h \
                widgetspagemodel.h \
                widgetspagelistmodel.h \
                widgetconfigurationhelper.h

SOURCES +=      contextbase_p.cpp \
                tools.cpp \
                version.cpp \
                identifiedelementinterface.cpp \
                widgetproviderbase.cpp \
                providermanager.cpp \
                abstractsettings_p.cpp \
                settings.cpp \
                settingsentry.cpp \
                graphicalcomponentbase.cpp \
                widgetbaseproperties.cpp \
                widgetproperties.cpp \
                gridmanager.cpp \
                widgetspagemodel.cpp \
                widgetspagelistmodel.cpp \
                widgetconfigurationhelper.cpp

include(deployment.pri)
