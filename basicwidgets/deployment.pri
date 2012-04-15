INSTALL_PATH = $${SYSTEM_WIDGETS_FOLDER}/$${TARGET}

# Path for target
target.path = $${INSTALL_PATH}
export(target.path)

# Path for desktop file
desktopFile.path = $${INSTALL_PATH}
desktopFile.files = $${DESKTOP_FILES}
export(desktopFile.path)
export(desktopFile.files)

INSTALLS += target desktopFile

# Subdirs
ANDROID_DOCK_FILES = android-dock/*

androidDockFiles.path = $${INSTALL_PATH}/android-dock
androidDockFiles.files = $${ANDROID_DOCK_FILES}
export(androidDockFiles.path)
export(androidDockFiles.files)

INSTALLS += androidDockFiles
