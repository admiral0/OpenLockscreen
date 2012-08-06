include(../../globals.pri)

# Path for QML files
qmlFiles.path = $${QML_FOLDER}
qmlFiles.files = $${QML_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

# Path for data files
dataFiles.path = $${DATA_FOLDER}
dataFiles.files = $${DATA_FILES}
export(dataFiles.path)
export(dataFiles.files)

# Path for target
target.path = $${APPLICATION_FOLDER}
export(target.path)

# Installs
INSTALLS += target qmlFiles dataFiles
