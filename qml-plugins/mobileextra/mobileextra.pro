TEMPLATE =      lib

TARGET =        widgetsmobileextra
QT +=           declarative
CONFIG +=       qt plugin

HEADERS +=      widgets_mobileextra_plugin.h \
                applicationinformations.h \
                foldermodel.h \
                foldermodel_p.h \
                applicationsmodel.h \

SOURCES +=      widgets_mobileextra_plugin.cpp \
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
