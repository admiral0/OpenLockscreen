TEMPLATE = subdirs

contains(CONFIG, mobile):!contains(CONFIG, desktop){
    SUBDIRS += mobile
}

contains(CONFIG, desktop):!contains(CONFIG, mobile){
    SUBDIRS += desktop
}
