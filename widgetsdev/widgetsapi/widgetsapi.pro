include(../../globals.pri)

QT       = core

TARGET = widgetsapi
TEMPLATE = lib

CONFIG += plugin

DEFINES += WIDGETSAPI_LIBRARY

HEADERS +=	widgetsapi_global.h \
            providerinterface.h \
            providerobject.h \
    declarativeplugin.h

include(deployment.pri)


