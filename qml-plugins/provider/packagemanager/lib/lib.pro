include(../../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = widgetspackagemanagerprovider
QT = core gui sql xml

contains(MEEGO_EDITION,harmattan):CONFIG += meegotouch

INCLUDEPATH += ../../../base/lib

HEADERS +=      componentbase.h \
                componentbase_p.h \
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

SOURCES +=      componentbase.cpp \
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

include(deployment.pri)
