TEMPLATE = subdirs
contains(CONFIG, pluginproviderbasic): SUBDIRS += basic
contains(CONFIG, pluginproviderpackagemanager): SUBDIRS += packagemanager

contains(CONFIG, mobile)|contains(CONFIG, desktop) {
    SUBDIRS += packagemanager
}
