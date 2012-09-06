# name
NAME = widgets

# version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 50


isEmpty(DEPLOYMENT_PREFIX)
{
    DEPLOYMENT_PREFIX = /usr
}

isEmpty(PREFIX) {
    CONFIG(release):PREFIX = /usr
    CONFIG(debug, debug|release):PREFIX = $${DEPLOYMENT_PREFIX}
}

DEFAULT_IMPORT_FOLDER = /usr/lib$${64_BITS}/qt4/imports/

# Default directories
isEmpty(BINDIR) {
    BINDIR = $${PREFIX}/bin
}
isEmpty(LIBDIR) {
    LIBDIR = $${PREFIX}/lib
}
isEmpty(IMPORTDIR) {
    CONFIG(noqtimport):{
        IMPORTDIR = $${PREFIX}/imports/
    } else {
        IMPORTDIR = $${DEFAULT_IMPORT_FOLDER}
    }
}
isEmpty(SHAREDIR) {
    SHAREDIR = $${PREFIX}/share/$${NAME}
}

isEmpty(OPTDIR) {
    OPTDIR = /opt/$${NAME}
}

isEmpty(INCLUDEDIR) {
    INCLUDEDIR = $${PREFIX}/include/$${NAME}
}

# Widgets folders
SYSTEM_WIDGETS_FOLDER = $${SHAREDIR}/widgets/
USER_WIDGETS_FOLDER =   $${OPTDIR}/widgets/

# Application + data + qml folders
contains(MEEGO_EDITION,harmattan):{
    APPLICATION_FOLDER  = $${OPTDIR}/bin/
    DATA_FOLDER = $${OPTDIR}/data/
    QML_FOLDER = $${OPTDIR}/qml/
} else {
    APPLICATION_FOLDER  = $${BINDIR}
    DATA_FOLDER = $${SHAREDIR}/data
    QML_FOLDER = $${SHAREDIR}/qml
}

# Test folder
TEST_FOLDER = $${SHAREDIR}/tests/

# Harmattan specific
contains(MEEGO_EDITION,harmattan):{
#    IMPORTDIR=/opt/widgets/
#    LIBDIR=/opt/widgets/lib/
    SYSTEM_WIDGETS_FOLDER = $${USER_WIDGETS_FOLDER}
}

# QML include folder
QML_PLUGIN_BASE_PATH = $${IMPORTDIR}/org/SfietKonstantin/
QML_PLUGIN_PATH = $${QML_PLUGIN_BASE_PATH}/$${NAME}


# Useful defines
DEFINES += 'SYSTEM_WIDGETS=\'\"$${SYSTEM_WIDGETS_FOLDER}\"\''
DEFINES += 'USER_WIDGETS=\'\"$${USER_WIDGETS_FOLDER}\"\''

DEFINES += 'WIDGETS_VERSION_MAJOR=$${VERSION_MAJOR}'
DEFINES += 'WIDGETS_VERSION_MINOR=$${VERSION_MINOR}'
DEFINES += 'WIDGETS_VERSION_PATCH=$${VERSION_PATCH}'

# Config overriding
contains(CONFIG, mobile)|contains(CONFIG, desktop) {
    CONFIG += plugincolors pluginbackground plugindocks plugininfo plugindrag extra
    CONFIG += pluginproviderpackagemanager
}

contains(CONFIG, examples) {
    CONFIG += plugincolors pluginbackground plugindocks plugininfo plugindrag
    CONFIG += pluginproviderbasic
}

contains(CONFIG, tests) {
    CONFIG += plugincolors pluginbackground plugindocks plugininfo plugindrag extra
    CONFIG += pluginproviderbasic pluginproviderpackagemanager
}
