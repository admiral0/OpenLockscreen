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
#ICON_FILES =            widgets/analogic-clock/metadata.desktop \
#                        widgets/analogic-clock/AnalogicClock.qml \
#                        widgets/analogic-clock/analogic-clock-background.png \
#                        widgets/analogic-clock/analogic-clock-night-background.png \
#                        widgets/analogic-clock/analogic-clock-center.png \
#                        widgets/analogic-clock/analogic-clock-hour.png \
#                        widgets/analogic-clock/analogic-clock-minute.png \

#iconFiles.path = $${INSTALL_PATH}/widgets/icon
#iconFiles.files = $${ANALOGIC_CLOCK_FILES}
#export(iconFiles.path)
#export(iconFiles.files)

INSTALLS += iconFiles
