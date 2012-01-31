unix {
    !isEmpty(MEEGO_VERSION_MAJOR) {
        installPath = $${EXTENSION_FOLDER}
    } else {
        installPath = $${EXTENSION_FOLDER}
    }
}

qmlFiles.path = $${installPath}
qmlFiles.files = $${OTHER_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

target.path = $${installPath}
export(target.path)

INSTALLS += target qmlFiles
