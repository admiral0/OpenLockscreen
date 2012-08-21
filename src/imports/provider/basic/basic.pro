include(../../../../globals.pri)

TEMPLATE = subdirs
SUBDIRS += widget
contains(CONFIG, plugindocks): SUBDIRS += mixed

