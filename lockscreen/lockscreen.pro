include(../globals.pri)

TEMPLATE =      lib
INCLUDEPATH += ../widgets/ ../widgetsdev/widgetsapi/

TARGET =        sysuid-screenlock

QT +=           declarative #xml
CONFIG +=       qt plugin gui meegotouch system-ui

HEADERS +=      screenlockextensioninterface.h \
                screenlockextension.h \
                lockscreen.h \
                lockscreenmanager.h \
                ../widgets/global.h \
                ../widgets/oxygencolors.h \
                ../widgets/settings.h \
#                ../widgets/settingswithdefault.h \
                ../widgets/settingswrapper.h \
#                ../widgets/mappableelementinterface.h \
#                ../widgets/identifiedelementinterface.h \
#                ../widgets/elementsettings.h \
#                ../widgets/widgetbaseproperties.h \
#                ../widgets/widgetproperties.h \
#                ../widgets/dockbaseproperties.h \
#                ../widgets/dockproperties.h \
#                ../widgets/availablewidgetsmodel.h \
#                ../widgets/availabledocksmodel.h \
#                ../widgets/package.h \
#                ../widgets/packagemanager.h \
#                ../widgets/displayedpagesmodel.h \
#                ../widgets/displayedpagewidgetsmodel.h \
#                ../widgets/displayeddocksmodel.h \
#                ../widgets/foldermodel.h \
#                ../widgets/applicationinformations.h \
#                ../widgets/applicationsmodel.h \
#                ../widgets/viewmanager.h \
#                ../widgets/launchermanager.h \
#                ../widgets/pluginmanager.h
    debughelper.h

SOURCES +=      screenlockextension.cpp \
                lockscreen.cpp \
                lockscreenmanager.cpp \
                ../widgets/oxygencolors.cpp \
                ../widgets/settings.cpp \
#                ../widgets/settingswithdefault.cpp \
                ../widgets/settingswrapper.cpp \
#                ../widgets/identifiedelementinterface.cpp \
#                ../widgets/elementsettings.cpp \
#                ../widgets/widgetbaseproperties.cpp \
#                ../widgets/widgetproperties.cpp \
#                ../widgets/dockbaseproperties.cpp \
#                ../widgets/dockproperties.cpp \
#                ../widgets/availablewidgetsmodel.cpp \
#                ../widgets/availabledocksmodel.cpp \
#                ../widgets/package.cpp \
#                ../widgets/packagemanager.cpp \
#                ../widgets/displayedpagesmodel.cpp \
#                ../widgets/displayedpagewidgetsmodel.cpp \
#                ../widgets/displayeddocksmodel.cpp \
#                ../widgets/foldermodel.cpp \
#                ../widgets/applicationinformations.cpp \
#                ../widgets/applicationsmodel.cpp \
#                ../widgets/viewmanager.cpp \
#                ../widgets/launchermanager.cpp \
#                ../widgets/pluginmanager.cpp
    debughelper.cpp

DESKTOP_FILE += sysuid-screenlock.desktop

include(deployment.pri)
