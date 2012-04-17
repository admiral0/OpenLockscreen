# Path for target
target.path = $${LIB_FOLDER}
export(target.path)

message($${LIB_FOLDER})

# Installs
INSTALLS += target #headerFiles
