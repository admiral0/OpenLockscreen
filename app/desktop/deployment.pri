include(../../globals.pri)

# Path for QML files
qmlFiles.path = $${SHAREDIR}/qml
qmlFiles.files = $${QML_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

# Path for data files
dataFiles.path = $${SHAREDIR}/data
dataFiles.files = $${DATA_FILES}
export(dataFiles.path)
export(dataFiles.files)

# Path for target
target.path = $${BINDIR}
export(target.path)

# Installs
INSTALLS += target qmlFiles dataFiles
