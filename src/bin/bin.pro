include(../../globals.pri)

TEMPLATE = subdirs
contains(CONFIG, pluginproviderpackagemanager): SUBDIRS += packagemanagerhelper
