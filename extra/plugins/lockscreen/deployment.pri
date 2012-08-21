installPath = /opt/widgets/lockscreen/

target.path = $${installPath}/lib/meegotouch/applicationextensions/
export(target.path)

qmlFiles.path = $${installPath}/qml/
qmlFiles.files = $${OTHER_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

desktopFile.path = $${installPath}/share/meegotouch/applicationextensions/
desktopFile.files = $${DESKTOP_FILE}
export(desktopFile.path)
export(desktopFile.files)

INSTALLS += target desktopFile qmlFiles
