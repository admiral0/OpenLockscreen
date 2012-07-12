include(../../globals.pri)

contains(MEEGO_EDITION,harmattan): {
    # Path for the desktop file
    desktopfile.files = $${TARGET}.desktop
    desktopfile.path = /usr/share/applications
    export(desktopfile.files)
    export(desktopfile.path)

    # Path for the icon file
    icon.files = $${TARGET}.png
    icon.path = /usr/share/icons/hicolor/80x80/apps
    export(icon.files)
    export(icon.path)
}

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
contains(MEEGO_EDITION,harmattan):INSTALLS += desktopfile icon
