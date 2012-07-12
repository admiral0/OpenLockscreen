include(../../globals.pri)

TEMPLATE =          app
TARGET =            widgets

QT =                core gui declarative xml

DEFINES +=          'MAIN_QML_PATH=\'\"$${SHAREDIR}/qml/main.qml\"\''

SOURCES +=          main.cpp \

#QML_FILES +=        qml/main.qml \
#                    qml/UiConstants.js \
#                    qml/HorizontalSeparator.qml \
#                    qml/ClickableEntry.qml \
#                    qml/CheckableEntry.qml \
#                    qml/AbstractPage.qml \
#                    qml/AbstractNavigationPage.qml \
#                    qml/MainPage.qml \
#                    qml/WidgetsPage.qml \
#                    qml/SettingsPage.qml \
#                    qml/DockEditorPage.qml \
#                    qml/WidgetEditorPage.qml \
#                    qml/Background.qml \
#                    qml/InformationsPage.qml \
#                    qml/PackageListPage.qml \
#                    qml/PackageDetailPage.qml \
#                    qml/DockListPage.qml \
#                    qml/WidgetListPage.qml \
#                    qml/AboutPage.qml \

#DATA_FILES +=       data/wallpaper-1.jpg \


include(deployment.pri)


