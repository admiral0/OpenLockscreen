include(../globals.pri)

WIDGETS_FILES +=    widgets/widgets.txt \
                    widgets/Dummy.qml

widgetsFiles.path = $${SYSTEM_WIDGETS_FOLDER}/widgets
widgetsFiles.files = $${WIDGETS_FILES}
export(widgetsFiles.path)
export(widgetsFiles.files)

BASE_QML_FILES +=   base/Banner.qml \
                    base/Button.qml \

baseQmlFiles.path = $${SHAREDIR}/examples/base
baseQmlFiles.files = $${BASE_QML_FILES}
export(baseQmlFiles.path)
export(baseQmlFiles.files)

INSTALLS += widgetsFiles baseQmlFiles
