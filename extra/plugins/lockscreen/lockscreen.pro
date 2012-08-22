TEMPLATE =      lib

TARGET =        sysuid-screenlock

QT +=           dbus declarative
CONFIG +=       qt plugin gui meegotouch system-ui qmsystem2

HEADERS +=      screenlockextensioninterface.h \
                screenlockextension.h \
                lockscreen.h \
                lockscreenmanager.h \
#                notification/notificationmanager.h \
#                notification/notification.h \
#                notification/notificationgroup.h \
#                notification/notificationmanagerinterface.h \
#                notification/eventtypestore.h \
#                notification/notificationparameter.h \
#                notification/notificationparameters.h \
                notificationsmodel.h \
    settingsmanager.h


SOURCES +=      screenlockextension.cpp \
                lockscreen.cpp \
                lockscreenmanager.cpp \
                notificationsmodel.cpp \
    settingsmanager.cpp

DESKTOP_FILE += sysuid-screenlock.desktop

# DATA_FILES +=   data/background.png \

OTHER_FILES +=  qml/main.qml \

include(deployment.pri)
