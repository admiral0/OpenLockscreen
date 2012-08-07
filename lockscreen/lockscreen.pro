TEMPLATE =      lib

TARGET =        sysuid-screenlock

QT +=           declarative
CONFIG +=       qt plugin gui meegotouch system-ui

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
                notificationsmodel.h


SOURCES +=      screenlockextension.cpp \
                lockscreen.cpp \
                lockscreenmanager.cpp \
                notificationsmodel.cpp

DESKTOP_FILE += sysuid-screenlock.desktop

# DATA_FILES +=   data/background.png \

OTHER_FILES +=  qml/main.qml \

include(deployment.pri)
