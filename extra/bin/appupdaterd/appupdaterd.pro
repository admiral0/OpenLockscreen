include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}-appupdaterd
QT = core dbus
SOURCES += main.cpp

include(deployment.pri)
