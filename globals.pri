# QML plugins
QML_PLUGIN_FOLDER =         /usr/lib/qt4/imports/org/SfietKonstantin/widgets/

# Widgets API
INCLUDE_FOLDER =            /usr/include/widgets/
LIB_FOLDER =                /usr/lib/widgets/

# Widgets folders
SYSTEM_WIDGETS_FOLDER =     /usr/share/widgets/
USER_WIDGETS_FOLDER =       /opt/widgets/widgets/

# Application folder
APPLICATION_FOLDER  =       /opt/widgets/

# Testing on Unix
unix {
    !contains(MEEGO_EDITION,harmattan):CONFIG(debug, debug|release): {
        QML_PLUGIN_FOLDER = $${DEPLOYMENT_PREFIX}/usr/lib/qt4/imports/org/SfietKonstantin/widgets/
        INCLUDE_FOLDER = $${DEPLOYMENT_PREFIX}/usr/include/widgets/
        LIB_FOLDER = $${DEPLOYMENT_PREFIX}/usr/lib/widgets/
        SYSTEM_WIDGETS_FOLDER = $${DEPLOYMENT_PREFIX}/usr/share/widgets/
        USER_WIDGETS_FOLDER = $${DEPLOYMENT_PREFIX}/opt/widgets/widgets/

        QML_PLUGIN_ROOT_FOLDER = $${DEPLOYMENT_PREFIX}/usr/lib/qt4/imports/
        DEFINES += 'QML_PLUGIN_PATH=\'\"$${QML_PLUGIN_ROOT_FOLDER}\"\''
    }
}

# Useful defines
DEFINES += 'SYSTEM_WIDGETS=\'\"$${SYSTEM_WIDGETS_FOLDER}\"\''
DEFINES += 'USER_WIDGETS=\'\"$${USER_WIDGETS_FOLDER}\"\''

DEFINES += 'WIDGETS_VERSION_MAJOR=1'
DEFINES += 'WIDGETS_VERSION_MINOR=0'
DEFINES += 'WIDGETS_VERSION_PATCH=0'
