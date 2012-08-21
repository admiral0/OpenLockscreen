include(../../globals.pri)

TEMPLATE = subdirs
contains(CONFIG, lockscreen):SUBDIRS += lockscreen
