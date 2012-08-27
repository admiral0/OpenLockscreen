include(../globals.pri)

installPath = $${SYSTEM_WIDGETS_FOLDER}/widgets

WIDGETS_FILES +=    widgets/widgets.txt \
                    widgets/Dummy.qml

widgetsFiles.path = $${installPath}
widgetsFiles.files = $${WIDGETS_FILES}
export(widgetsFiles.path)
export(widgetsFiles.files)

INSTALLS += widgetsFiles
