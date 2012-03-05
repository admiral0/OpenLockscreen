# Path for the desktop file
desktopfile.files = $${TARGET}.desktop
desktopfile.path = $${DEPLOYMENT_PREFIX}/usr/share/applications
export(desktopfile.files)
export(desktopfile.path)

# Path for the icon file
icon.files = $${TARGET}.png
icon.path = $${DEPLOYMENT_PREFIX}/usr/share/icons/hicolor/80x80/apps
export(icon.files)
export(icon.path)

# Path for QML files
qmlFiles.path = $${DEPLOYMENT_PREFIX}/$${APPLICATION_FOLDER}/qml
qmlFiles.files = $${QML_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

# Path for data files
dataFiles.path = $${DEPLOYMENT_PREFIX}/$${APPLICATION_FOLDER}/data
dataFiles.files = $${DATA_FILES}
export(dataFiles.path)
export(dataFiles.files)

# Path for target
target.path = $${DEPLOYMENT_PREFIX}/$${APPLICATION_FOLDER}/bin
export(target.path)

# Installs
INSTALLS += target qmlFiles dataFiles desktopfile icon
