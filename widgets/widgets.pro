include(../globals.pri)

TEMPLATE =          app
TARGET =            widgets

QT =                core gui declarative xml
CONFIG +=           qdeclarative-boostable
#INCLUDEPATH += ../widgetsdev/widgetsapi/

DEFINES +=          'MAIN_QML_PATH=\'\"$${APPLICATION_FOLDER}/qml/main.qml\"\''

SOURCES +=          main.cpp \

QML_FILES +=        qml/main.qml \


# DATA_FILES +=       data/splash.jpg \


include(deployment.pri)
