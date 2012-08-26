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

SWIPE_UNLOCK_FILES =    docks/swipe-unlock/metadata.desktop \
                        docks/swipe-unlock/SwipeUnlock.qml \
                        docks/swipe-unlock/arrow.png \

ANALOGIC_CLOCK_FILES =  widgets/analogic-clock/metadata.desktop \
                        widgets/analogic-clock/AnalogicClock.qml \
                        widgets/analogic-clock/analogic-clock-background.png \
                        widgets/analogic-clock/analogic-clock-night-background.png \
                        widgets/analogic-clock/analogic-clock-center.png \
                        widgets/analogic-clock/analogic-clock-hour.png \
                        widgets/analogic-clock/analogic-clock-minute.png \

HARMATTAN_CLOCK_FILES = widgets/harmattan-clock/metadata.desktop \
                        widgets/harmattan-clock/HarmattanClock.qml \

PICTURE_FRAME_FILES =   widgets/picture-frame/metadata.desktop \
                        widgets/picture-frame/PictureFrame.qml \
                        widgets/picture-frame/PictureFrameSettings.qml \

ICLOCK_FILES =          widgets/iclock/metadata.desktop \
                        widgets/iclock/iClock.qml \

androidDockFiles.path = $${installPath}/docks/android-dock
androidDockFiles.files = $${ANDROID_DOCK_FILES}
export(androidDockFiles.path)
export(androidDockFiles.files)

maemoDockFiles.path = $${installPath}/docks/maemo-dock
maemoDockFiles.files = $${MAEMO_DOCK_FILES}
export(maemoDockFiles.path)
export(maemoDockFiles.files)

swipeUnlockFiles.path = $${installPath}/docks/swipe-unlock
swipeUnlockFiles.files = $${SWIPE_UNLOCK_FILES}
export(swipeUnlockFiles.path)
export(swipeUnlockFiles.files)

analogicClockFiles.path = $${installPath}/widgets/analogic-clock
analogicClockFiles.files = $${ANALOGIC_CLOCK_FILES}
export(analogicClockFiles.path)
export(analogicClockFiles.files)

harmattanClockFiles.path = $${installPath}/widgets/harmattan-clock
harmattanClockFiles.files = $${HARMATTAN_CLOCK_FILES}
export(harmattanClockFiles.path)
export(harmattanClockFiles.files)

pictureFrameFiles.path = $${installPath}/widgets/picture-frame
pictureFrameFiles.files = $${PICTURE_FRAME_FILES}
export(pictureFrameFiles.path)
export(pictureFrameFiles.files)

iClockFiles.path = $${installPath}/widgets/iclock
iClockFiles.files = $${ICLOCK_FILES}
export(iClockFiles.path)
export(iClockFiles.files)

INSTALLS += androidDockFiles maemoDockFiles swipeUnlockFiles
INSTALLS += analogicClockFiles harmattanClockFiles pictureFrameFiles iClockFiles
