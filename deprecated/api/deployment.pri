include(../globals.pri)

# Path for headers
headerFiles.path = $${INCLUDEDIR}
headerFiles.files = $${HEADERS}
export(headerFiles.path)
export(headerFiles.files)

# Path for target
target.path = $${LIBDIR}
export(target.path)

# Installs
INSTALLS += target headerFiles
