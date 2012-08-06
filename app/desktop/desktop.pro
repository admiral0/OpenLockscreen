include(../../globals.pri)

TEMPLATE =          app
TARGET =            widgets

QT =                core gui declarative xml

DEFINES +=          'MAIN_QML_PATH=\'\"$${QML_FOLDER}/main.qml\"\''
DEFINES +=          'IMPORT_DIR=\'\"$${IMPORTDIR}\"\''
DEFINES +=          'DATA_DIR=\'\"$${DATA_FOLDER}\"\''

SOURCES +=          main.cpp \

QML_FILES +=        qml/main.qml \
                    qml/Icon.qml \
                    qml/IconRow.qml \
                    qml/Toolbar.qml \
                    qml/Page.qml \
                    qml/PageStack.qml \
                    qml/ClickableEntry.qml \
                    qml/Main.qml \
                    qml/WidgetView.qml \
                    qml/Informations.qml \
                    qml/PackageInformations.qml \
                    qml/DockInformations.qml \
                    qml/WidgetInformations.qml \

DATA_FILES +=       data/configure.png \
                    data/list-add.png \
                    data/edit-undo.png \


include(deployment.pri)



