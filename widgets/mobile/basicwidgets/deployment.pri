include(../../../globals.pri)

installPath = $${SYSTEM_WIDGETS_FOLDER}/$${TARGET}

# Path for target
target.path = $${installPath}
export(target.path)

# Path for desktop file
desktopFile.path = $${installPath}
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

PLAIN_TEXT_FILES =      widgets/plain-text/metadata.desktop \
                        widgets/plain-text/PlainText.qml \
                        widgets/plain-text/PlainTextSettings.qml \

androidDockFiles.path = $${installPath}/docks/android-dock
androidDockFiles.files = $${ANDROID_DOCK_FILES}
export(androidDockFiles.path)
export(androidDockFiles.files)

maemoDockFiles.path = $${installPath}/docks/maemo-dock
maemoDockFiles.files = $${MAEMO_DOCK_FILES}
export(maemoDockFiles.path)
export(maemoDockFiles.files)

analogicClockFiles.path = $${installPath}/widgets/analogic-clock
analogicClockFiles.files = $${ANALOGIC_CLOCK_FILES}
export(analogicClockFiles.path)
export(analogicClockFiles.files)

plainTextFiles.path = $${installPath}/widgets/plain-text
plainTextFiles.files = $${PLAIN_TEXT_FILES}
export(plainTextFiles.path)
export(plainTextFiles.files)

INSTALLS += androidDockFiles maemoDockFiles analogicClockFiles plainTextFiles
