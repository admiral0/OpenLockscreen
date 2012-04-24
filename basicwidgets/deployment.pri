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
ANDROID_DOCK_FILES =    docks/android-dock/metadata.desktop \
                        docks/android-dock/AndroidDock.qml \
                        docks/android-dock/AndroidDockButton.qml \
                        docks/android-dock/android-call.png \
                        docks/android-dock/android-internet.png \
                        docks/android-dock/android-menu.png \

MAEMO_DOCK_FILES =      docks/maemo-dock/metadata.desktop \
                        docks/maemo-dock/MaemoDock.qml \
                        docks/maemo-dock/MaemoDockButton.qml \
                        docks/maemo-dock/maemo-menu.png \

ANALOGIC_CLOCK_FILES =  widgets/analogic-clock/metadata.desktop \
                        widgets/analogic-clock/AnalogicClock.qml \
                        widgets/analogic-clock/analogic-clock-background.png \
                        widgets/analogic-clock/analogic-clock-night-background.png \
                        widgets/analogic-clock/analogic-clock-center.png \
                        widgets/analogic-clock/analogic-clock-hour.png \
                        widgets/analogic-clock/analogic-clock-minute.png \

androidDockFiles.path = $${INSTALL_PATH}/docks/android-dock
androidDockFiles.files = $${ANDROID_DOCK_FILES}
export(androidDockFiles.path)
export(androidDockFiles.files)

maemoDockFiles.path = $${INSTALL_PATH}/docks/maemo-dock
maemoDockFiles.files = $${MAEMO_DOCK_FILES}
export(maemoDockFiles.path)
export(maemoDockFiles.files)

analogicClock.path = $${INSTALL_PATH}/widgets/analogic-clock
analogicClock.files = $${ANALOGIC_CLOCK_FILES}
export(analogicClock.path)
export(analogicClock.files)

INSTALLS += androidDockFiles maemoDockFiles analogicClock
