unix {
    !isEmpty(MEEGO_VERSION_MAJOR) {
        installPath = $${DEPLOYMENT_PREFIX}/opt/$${APP_FOLDER}/$${WIDGETS_FOLDER}/$${TARGET}
    } else {
        installPath = $${DEPLOYMENT_PREFIX}/$${WIDGETS_FOLDER}/$${TARGET}
    }
}

qmlFiles.path = $${installPath}
qmlFiles.files = $${OTHER_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

dataFiles.path = $${installPath}/data
dataFiles.files = $${DATA_FILES}
export(dataFiles.path)
export(dataFiles.files)

INSTALLS += qmlFiles dataFiles
