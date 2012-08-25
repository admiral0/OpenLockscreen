include(../../../globals.pri)

# Path for target
target.path = $${APPLICATION_FOLDER}
export(target.path)

# Path for daemon
daemonFile.path = /etc/init/apps
daemonFile.files = widgets-appupdaterd.conf
export(daemonFile.path)
export(daemonFile.files)

# Installs
INSTALLS += target daemonFile
