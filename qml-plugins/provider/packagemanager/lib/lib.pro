include(../../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = widgetspackagemanagerprovider
QT = core gui sql

contains(MEEGO_EDITION,harmattan):CONFIG += meegotouch

INCLUDEPATH += ../../../base/lib
INCLUDEPATH += ../../../docks/lib
LIBS += -L../../../base/lib/ -lwidgetsbase
LIBS += -L../../../docks/lib/ -lwidgetsdocks

HEADERS +=      desktopfileparser_p.h \
                desktopcomponent_p.h \
                desktopcomponent.h \
                package.h \
                componentmetadata_p.h \
                filtercondition.h \
                filterconditionlist.h \
                packagemanager.h \
                packagemanager_p.h \
                databaseinterface_p.h \
                databaseinterface_p_p.h \

SOURCES +=      desktopfileparser_p.cpp \
                desktopcomponent.cpp \
                package.cpp \
                componentmetadata_p.cpp \
                filtercondition.cpp \
                filterconditionlist.cpp \
                packagemanager.cpp \
                databaseinterface_p.cpp \

include(deployment.pri)
