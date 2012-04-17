# version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 0

# 64 bits if needed
contains(QMAKE_HOST.arch, x86_64): {
    64_BITS = 64
}

# QML plugins
QML_PLUGIN_FOLDER =         /usr/lib$${64_BITS}/qt4/imports/org/SfietKonstantin/widgets/

# Widgets API
INCLUDE_FOLDER =            /usr/include/widgets/
LIB_FOLDER =                /usr/lib$${64_BITS}/

# Widgets folders
SYSTEM_WIDGETS_FOLDER =     /usr/share/widgets/
USER_WIDGETS_FOLDER =       /opt/widgets/widgets/

# Application folder
APPLICATION_FOLDER  =       /opt/widgets/

# Test folder
TEST_FOLDER =               /opt/widgets/tests/

# Testing on Unix
unix {
    !contains(MEEGO_EDITION,harmattan):CONFIG(debug, debug|release): {
        QML_PLUGIN_FOLDER =     $${DEPLOYMENT_PREFIX}/usr/lib$${64_BITS}/qt4/imports/org/SfietKonstantin/widgets/
        INCLUDE_FOLDER =        $${DEPLOYMENT_PREFIX}/usr/include/widgets/
        LIB_FOLDER =            $${DEPLOYMENT_PREFIX}/usr/lib$${64_BITS}/
        SYSTEM_WIDGETS_FOLDER = $${DEPLOYMENT_PREFIX}/usr/share/widgets/
        USER_WIDGETS_FOLDER =   $${DEPLOYMENT_PREFIX}/opt/widgets/widgets/

        QML_PLUGIN_ROOT_FOLDER = $${DEPLOYMENT_PREFIX}/usr/lib$${64_BITS}/qt4/imports/
        DEFINES += 'QML_PLUGIN_PATH=\'\"$${QML_PLUGIN_ROOT_FOLDER}\"\''
    }
}

# Useful defines
DEFINES += 'SYSTEM_WIDGETS=\'\"$${SYSTEM_WIDGETS_FOLDER}\"\''
DEFINES += 'USER_WIDGETS=\'\"$${USER_WIDGETS_FOLDER}\"\''

DEFINES += 'WIDGETS_VERSION_MAJOR=$${VERSION_MAJOR}'
DEFINES += 'WIDGETS_VERSION_MINOR=$${VERSION_MINOR}'
DEFINES += 'WIDGETS_VERSION_PATCH=$${VERSION_PATCH}'
