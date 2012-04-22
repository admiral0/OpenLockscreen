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
ANDROID_DOCK_FILES =    android-dock/metadata.desktop \
                        android-dock/AndroidDock.qml \
                        android-dock/AndroidDockButton.qml \
                        android-dock/android-call.png \
                        android-dock/android-internet.png \
                        android-dock/android-menu.png \

MAEMO_DOCK_FILES =      maemo-dock/metadata.desktop \
                        maemo-dock/MaemoDock.qml \
                        maemo-dock/MaemoDockButton.qml \
                        maemo-dock/maemo-menu.png \

androidDockFiles.path = $${INSTALL_PATH}/android-dock
androidDockFiles.files = $${ANDROID_DOCK_FILES}
export(androidDockFiles.path)
export(androidDockFiles.files)

maemoDockFiles.path = $${INSTALL_PATH}/maemo-dock
maemoDockFiles.files = $${MAEMO_DOCK_FILES}
export(maemoDockFiles.path)
export(maemoDockFiles.files)

INSTALLS += androidDockFiles maemoDockFiles
