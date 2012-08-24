include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}-packagemanagerhelper
QT = core gui
INCLUDEPATH +=../../lib/base/
INCLUDEPATH +=../../lib/docks/
INCLUDEPATH +=../../lib/packagemanager/
LIBS +=-L../../lib/base -lwidgetsbase
LIBS +=-L../../lib/docks -lwidgetsdocks
LIBS +=-L../../lib/packagemanager -lwidgetspackagemanager

SOURCES +=  main.cpp

include(deployment.pri)

