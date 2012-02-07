unix {
    !isEmpty(MEEGO_VERSION_MAJOR) {
        installPath = $${DEPLOYMENT_PREFIX}/opt/$${APP_FOLDER}/lib
        includePath = $${INCLUDE_FOLDER}
    } else {
        installPath = $${DEPLOYMENT_PREFIX}/opt/$${APP_FOLDER}/lib
        includePath = $${INCLUDE_FOLDER}
    }
}

headerFiles.path = $${includePath}
headerFiles.files = $${HEADERS}
export(headerFiles.path)
export(headerFiles.files)

target.path = $${installPath}
export(target.path)

INSTALLS += target
CONFIG(release, debug|release): INSTALLS += headerFiles
