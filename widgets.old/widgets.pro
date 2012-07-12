include(../globals.pri)

TEMPLATE =          app
TARGET =            widgets

QT =                core gui declarative xml
INCLUDEPATH += ../widgetsdev/widgetsapi/

HEADERS +=          global.h \
                    app.h \
                    oxygencolors.h \
                    settings.h \
                    settingswithdefault.h \
                    settingswrapper.h \
                    mappableelementinterface.h \
                    identifiedelementinterface.h \
                    elementsettings.h \
                    widgetbaseproperties.h \
                    widgetproperties.h \
                    dockbaseproperties.h \
                    dockproperties.h \
                    availablewidgetsmodel.h \
                    availabledocksmodel.h \
                    package.h \
                    packagemanager.h \
                    displayedpagesmodel.h \
                    displayedpagewidgetsmodel.h \
                    displayeddocksmodel.h \
                    foldermodel.h \
                    applicationinformations.h \
                    applicationsmodel.h \
                    viewmanager.h \
                    launchermanager.h \
    pluginmanager.h


SOURCES +=          main.cpp \
                    app.cpp \
                    oxygencolors.cpp \
                    settings.cpp \
                    settingswithdefault.cpp \
                    settingswrapper.cpp \
                    identifiedelementinterface.cpp \
                    elementsettings.cpp \
                    widgetbaseproperties.cpp \
                    widgetproperties.cpp \
                    dockbaseproperties.cpp \
                    dockproperties.cpp \
                    availablewidgetsmodel.cpp \
                    availabledocksmodel.cpp \
                    package.cpp \
                    packagemanager.cpp \
                    displayedpagesmodel.cpp \
                    displayedpagewidgetsmodel.cpp \
                    displayeddocksmodel.cpp \
                    foldermodel.cpp \
                    applicationinformations.cpp \
                    applicationsmodel.cpp \
                    viewmanager.cpp \
                    launchermanager.cpp \
    pluginmanager.cpp

QML_FILES +=        qml/main.qml \
                    qml/UiConstants.js \
                    qml/CheckableEntry.qml \
                    qml/Api.qml \
                    qml/MainPage.qml \
                    qml/Background.qml \
                    qml/Unlocker.qml \
                    qml/PagesView.qml \
                    qml/PageWidgetsView.qml \
                    qml/PageWidgetsBackground.qml \
                    qml/DragManager.qml \
                    qml/WidgetContainer.qml \
                    qml/WidgetDragger.qml \
                    qml/WidgetDraggerButton.qml \
                    qml/DocksView.qml \
                    qml/DockContainer.qml \
                    qml/MainPageToolbar.qml \
                    qml/MainPageToolbarMenu.qml \
                    qml/SelectorWidgetsSheet.qml \
                    qml/SelectorDocksSheet.qml \
                    qml/Launcher.qml \
                    qml/LauncherGrid.qml \
                    qml/LauncherButton.qml \
                    qml/LauncherButtonIcon.qml \
                    qml/LauncherButtonIconFunctions.js \
                    qml/LauncherClickableEntry.qml \
                    qml/Icon.qml \
                    qml/internalwidgets.xml \


DATA_FILES +=       data/splash.jpg \
                    data/wallpaper-1.jpg \
                    data/wallpaper-1-thumbnail.jpg \
                    data/wallpaper-2.jpg \
                    data/wallpaper-2-thumbnail.jpg \
                    data/wallpaper-3.jpg \
                    data/wallpaper-3-thumbnail.jpg \
                    data/wallpaper-4.jpg \
                    data/wallpaper-4-thumbnail.jpg \
                    data/background.png \

include(deployment.pri)
