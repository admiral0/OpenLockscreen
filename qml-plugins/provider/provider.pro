include(../../globals.pri)

TEMPLATE = subdirs
contains(CONFIG, pluginproviderbasic): SUBDIRS += basic
contains(CONFIG, pluginproviderpackagemanager): SUBDIRS += packagemanager
