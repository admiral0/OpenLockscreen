include(../../../globals.pri)

installPath = $${QML_PLUGIN_BASE_PATH}/mobile/launcher

# Path for QML files
qmlFiles.path = $${installPath}
qmlFiles.files = $${OTHER_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

# Path for target
target.path = $${installPath}
export(target.path)

# Installs
INSTALLS += target qmlFiles
