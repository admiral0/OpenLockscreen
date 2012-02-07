include(../globals.pri)

TEMPLATE =      lib

TARGET =        basicwidgets

CONFIG +=       qt plugin

HEADERS +=      basicwidgets_plugin.h

OTHER_FILES =   basicwidgets.xml \
                AnalogicClock.qml \
                PictureFrame.qml \
                PictureFrameSettingsSheet.qml \
                Welcome.qml \
                AndroidDock.qml \
                AndroidDockButton.qml \
                MaemoDock.qml \


DATA_FILES =    data/analogic-clock-background.png \
                data/analogic-clock-night-background.png \
                data/analogic-clock-hour.png \
                data/analogic-clock-minute.png \
                data/analogic-clock-center.png\
                data/welcome.png \
                data/chat-bubble.svg \
                data/maemo-menu.png \
                data/android-call.png \
                data/android-menu.png \
                data/android-internet.png \

include(deployment.pri)
