include(../globals.pri)

TEMPLATE =          app
TARGET =            widgets-settings

QT =                core gui declarative

HEADERS +=          ../widgets/settings.h \
                    ../widgets/settingswithdefault.h \
                    ../widgets/elementsettings.h \
                    ../widgets/identifiedelementinterface.h \
                    ../widgets/dockbaseproperties.h \
                    ../widgets/dockproperties.h \
                    settingsmanager.h

SOURCES +=          main.cpp \
                    ../widgets/settings.cpp \
                    ../widgets/settingswithdefault.cpp \
                    ../widgets/elementsettings.cpp \
                    ../widgets/identifiedelementinterface.cpp \
                    ../widgets/dockbaseproperties.cpp \
                    ../widgets/dockproperties.cpp \
                    settingsmanager.cpp

QML_FILES +=        qml/main.qml \
                    qml/AbstractPage.qml \
                    qml/AbstractNavigationPage.qml \
                    qml/MainPage.qml \
                    qml/AboutPage.qml \
                    qml/WallpaperSourcePage.qml \
                    qml/WallpaperDefaultPage.qml \
                    qml/WallpaperPicturesPage.qml \




include(deployment.pri)
