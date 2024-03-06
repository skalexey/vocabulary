# macro(configure_files src_dir dest_dir)
# 	message(STATUS "Configuring directory ${dest_dir}")
# 	message(STATUS "Copy from ${src_dir}")
# 	make_directory(${dest_dir})

# 	file(GLOB files RELATIVE ${src_dir} ${src_dir}/*)
# 	foreach(file ${files})
# 		set(src_file_path ${src_dir}/${file})
# 		if(NOT IS_DIRECTORY ${src_file_path})
# 			message(STATUS "Configuring file ${file}")
# 			configure_file(
# 					${src_file_path}
# 					${dest_dir}/${file}
# 					COPYONLY)
# 		endif(NOT IS_DIRECTORY ${src_file_path})
# 	endforeach(file)
# endmacro(configure_files)

# Define a macro to recursively copy a directory's contents to the build directory
macro(copy_directory SOURCE DEST)
    # Create the destination directory if it doesn't exist
    file(MAKE_DIRECTORY ${DEST})

    # Copy the contents of the source directory to the destination directory
    file(COPY ${SOURCE} DESTINATION ${DEST})
endmacro()