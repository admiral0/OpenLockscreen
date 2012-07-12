TEMPLATE =      subdirs

SUBDIRS +=      qml-plugins api app

contains(CONFIG, mobile):SUBDIRS += corewidgets basicwidgets
contains(CONFIG, tests):SUBDIRS += tests

OTHER_FILES +=  qtc_packaging/debian_harmattan/rules \
                qtc_packaging/debian_harmattan/README \
                qtc_packaging/debian_harmattan/manifest.aegis \
                qtc_packaging/debian_harmattan/copyright \
                qtc_packaging/debian_harmattan/control \
                qtc_packaging/debian_harmattan/compat \
                qtc_packaging/debian_harmattan/changelog
