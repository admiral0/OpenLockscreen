include(../../globals.pri)

TEMPLATE = subdirs

SUBDIRS += base

contains(CONFIG, plugincolors): SUBDIRS += colors
contains(CONFIG, pluginbackground): SUBDIRS += background
contains(CONFIG, plugindocks): SUBDIRS += docks
contains(CONFIG, plugindrag): SUBDIRS += drag

SUBDIRS += provider

contains(CONFIG, plugininfo): SUBDIRS += info
