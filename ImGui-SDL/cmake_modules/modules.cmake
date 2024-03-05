macro(modules_include_all dir)
	include(${dir}/build_directory.cmake)
	include(${dir}/compile.cmake)
	include(${dir}/deps.cmake)
	include(${dir}/group.cmake)
	include(${dir}/includes.cmake)
	include(${dir}/inherit_parent.cmake)
	include(${dir}/log.cmake)
	include(${dir}/module.cmake)
	include(${dir}/src.cmake)
	include(${dir}/qt.cmake)
	include(${dir}/platforms.cmake)
endmacro(modules_include_all)

macro(setup_module_project)
	# Include all modules

	set(CMAKE_CXX_STANDARD 17)
	
	# Make FetchContent_Populate work in offline
	set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

	module_message("Setup project ${PROJECT_NAME}")
	
	# Setup helper variables
	get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

	# Common setup actions
	cpp_compile_options_fixes()
	set_module_name(${PROJECT_NAME})
	setup_inherit_parent()
	setup_log()
	
	set_build_directory()
	setup_deps()
	check_extra_includes()
	
	# Give control to the user
	setup_module()

	# Post-user actions
endmacro(setup_module_project)