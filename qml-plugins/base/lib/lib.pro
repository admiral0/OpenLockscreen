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
                widgetproviderinterface.h \
                abstractsettings_p.h \
                settings.h \
                settingsentry.h \
                graphicalcomponentbase_p.h \
                graphicalcomponentbase.h \
                gridmanager.h \
#                dockmodel.h \
#                widgetspagemodel.h \
#                widgetspagelistmodel.h \
#                configurationmanager.h \

SOURCES +=      tools.cpp \
                version.cpp \
                identifiedelementinterface.cpp \
                abstractsettings_p.cpp \
                settings.cpp \
                settingsentry.cpp \
                graphicalcomponentbase.cpp \
                gridmanager.cpp
#                dockmodel.cpp \
#                widgetspagemodel.cpp \
#                widgetspagelistmodel.cpp \
#                configurationmanager.cpp \

include(deployment.pri)
