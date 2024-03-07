# Define a macro to recursively copy a directory's contents to the build directory
macro(copy_directory SOURCE DEST)
    # Create the destination directory if it doesn't exist
    file(MAKE_DIRECTORY ${DEST})

    # Copy the contents of the source directory to the destination directory
    file(COPY ${SOURCE} DESTINATION ${DEST})
endmacro()