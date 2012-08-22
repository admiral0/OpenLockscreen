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
ICON_FILES =            widgets/icon/metadata.desktop \
                        widgets/icon/Icon.qml \
#                        widgets/analogic-clock/analogic-clock-background.png \
#                        widgets/analogic-clock/analogic-clock-night-background.png \
#                        widgets/analogic-clock/analogic-clock-center.png \
#                        widgets/analogic-clock/analogic-clock-hour.png \
#                        widgets/analogic-clock/analogic-clock-minute.png \

iconFiles.path = $${installPath}/widgets/icon
iconFiles.files = $${ICON_FILES}
export(iconFiles.path)
export(iconFiles.files)

INSTALLS += iconFiles
