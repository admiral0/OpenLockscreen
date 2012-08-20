include(../../globals.pri)

TEMPLATE = subdirs
SUBDIRS += widget
contains(CONFIG, plugindocks): SUBDIRS += dock
contains(CONFIG, pluginproviderpackagemanager): SUBDIRS += packagemanager
