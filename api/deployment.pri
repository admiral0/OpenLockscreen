# Path for headers
headerFiles.path = $${INCLUDE_FOLDER}
headerFiles.files = $${HEADERS}
export(headerFiles.path)
export(headerFiles.files)

# Path for target
target.path = $${LIB_FOLDER}
export(target.path)

# Installs
INSTALLS += target headerFiles
