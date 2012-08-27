TEMPLATE = subdirs

contains(CONFIG, desktop):!contains(CONFIG, mobile){
    SUBDIRS += desktop
}
