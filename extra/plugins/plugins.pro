include(../../globals.pri)

TEMPLATE = subdirs

contains(MEEGO_EDITION, harmattan):{
    contains(CONFIG, lockscreen):SUBDIRS += lockscreen
}
