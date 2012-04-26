TEMPLATE =      subdirs

SUBDIRS +=      qml-plugins api

contains(WIDGETS_OPTIONS, application):SUBDIRS += widgets corewidgets basicwidgets
contains(WIDGETS_OPTIONS, tests):SUBDIRS += tests

OTHER_FILES +=  qtc_packaging/debian_harmattan/rules \
                qtc_packaging/debian_harmattan/README \
                qtc_packaging/debian_harmattan/manifest.aegis \
                qtc_packaging/debian_harmattan/copyright \
                qtc_packaging/debian_harmattan/control \
                qtc_packaging/debian_harmattan/compat \
                qtc_packaging/debian_harmattan/changelog
