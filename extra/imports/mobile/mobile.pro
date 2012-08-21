TEMPLATE =      lib

TARGET =        mobilelauncher
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      mobile_launcher_plugin.h \
                applicationinformations.h \
                foldermodel.h \
                foldermodel_p.h \
                applicationsmodel.h \

SOURCES +=      mobile_launcher_plugin.cpp \
                applicationinformations.cpp \
                foldermodel.cpp \
                applicationsmodel.cpp \

OTHER_FILES =   qmldir \
                UiConstants.js \
                LauncherButtonIconFunctions.js \
                LauncherButtonIcon.qml \
                LauncherButton.qml \
                LauncherGrid.qml \
                Launcher.qml \


include(deployment.pri)
