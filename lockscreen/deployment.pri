installPath = $${DEPLOYMENT_PREFIX}/opt/$${APP_FOLDER}/screenlock

target.path = $${installPath}/lib/meegotouch/applicationextensions/
export(target.path)

desktopFile.path = $${installPath}/share/meegotouch/applicationextensions/
desktopFile.files = $${DESKTOP_FILE}
export(desktopFile.path)
export(desktopFile.files)

INSTALLS += target desktopFile
