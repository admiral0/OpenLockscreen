include(../../globals.pri)

TEMPLATE = app
TARGET = example1
QT = core gui declarative

installPrefix = $${SHAREDIR}/examples/example1

CONFIG(noqtimport):DEFINES += 'IMPORT_DIR=\'\"$${IMPORTDIR}\"\''
DEFINES += 'MAIN_QML_PATH=\'\"$${installPrefix}/main.qml\"\''
DEFINES += 'WIDGETS_PROVIDER_FILE=\'\"$${SYSTEM_WIDGETS_FOLDER}/widgets/\"\''

SOURCES +=      main.cpp

OTHER_FILES +=  main.qml \

# Deployment
target.path = $${installPrefix}

qmlFiles.files = $${OTHER_FILES}
qmlFiles.path = $${installPrefix}

INSTALLS += target qmlFiles
