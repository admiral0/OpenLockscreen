include(../../globals.pri)

TEMPLATE = subdirs
contains(MEEGO_EDITION, harmattan):{
    contains(CONFIG, mobile):SUBDIRS += appupdaterd
}
contains(CONFIG, mobile):!contains(CONFIG, desktop){
    SUBDIRS += app
}
