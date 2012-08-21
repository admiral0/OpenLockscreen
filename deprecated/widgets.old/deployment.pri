unix {
    !isEmpty(MEEGO_VERSION_MAJOR) {
        DEFINES += HARMATTAN_BOOSTER

        desktopfile.files = $${TARGET}.desktop
        desktopfile.path = $${DEPLOYMENT_PREFIX}/usr/share/applications
        icon.files = $${TARGET}.png
        icon.path = $${DEPLOYMENT_PREFIX}/usr/share/icons/hicolor/80x80/apps

        qmlInstallPath = $${DEPLOYMENT_PREFIX}/opt/$${APP_FOLDER}/qml
        dataInstallPath = $${DEPLOYMENT_PREFIX}/opt/$${APP_FOLDER}/data
        targetInstallPath = $${DEPLOYMENT_PREFIX}/opt/$${APP_FOLDER}/bin
    } else {
        qmlInstallPath = $${DEPLOYMENT_PREFIX}/$${TARGET}/qml
        dataInstallPath = $${DEPLOYMENT_PREFIX}/$${TARGET}/data
        targetInstallPath = $${DEPLOYMENT_PREFIX}/$${TARGET}/bin
    }
}

!isEmpty(desktopfile.path) {
    export(desktopfile.files)
    export(desktopfile.path)

    INSTALLS += desktopfile
}

!isEmpty(icon.path) {
    export(icon.files)
    export(icon.path)

    INSTALLS += icon
}

qmlFiles.path = $${qmlInstallPath}
qmlFiles.files = $${QML_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

dataFiles.path = $${dataInstallPath}
dataFiles.files = $${DATA_FILES}
export(dataFiles.path)
export(dataFiles.files)

target.path = $${targetInstallPath}
export(target.path)

INSTALLS += target qmlFiles dataFiles
