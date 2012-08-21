include(../../globals.pri)

TEMPLATE = subdirs

SUBDIRS = base

contains(CONFIG, plugindocks): SUBDIRS += docks
contains(CONFIG, pluginproviderpackagemanager): SUBDIRS += packagemanager
