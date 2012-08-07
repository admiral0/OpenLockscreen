TEMPLATE =  subdirs

SUBDIRS += base
contains(CONFIG, plugincolors): SUBDIRS += colors
contains(CONFIG, pluginbackground): SUBDIRS += background
contains(CONFIG, plugindocks):!contains(CONFIG, nodocks): SUBDIRS += docks
contains(CONFIG, pluginextra): SUBDIRS += drag
contains(CONFIG, plugindrag): SUBDIRS += extra

contains(CONFIG, mobile)|contains(CONFIG, desktop) {
    SUBDIRS += colors background docks extra drag
}
