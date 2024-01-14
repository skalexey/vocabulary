macro(setup_generator_short_name)
	# module_message("CMAKE_GENERATOR: ${CMAKE_GENERATOR}")
	# module_message("CMAKE_VS_PLATFORM_NAME: ${CMAKE_VS_PLATFORM_NAME}")
	# module_message("CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
	# module_message("CMAKE_VS_PLATFORM_TOOLSET_VERSION: ${CMAKE_VS_PLATFORM_TOOLSET_VERSION}")
	if (CMAKE_GENERATOR MATCHES "Visual Studio")
		string(REGEX MATCH "^[0-9]+" _MSVC_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
		# Check the platform name
		if (CMAKE_VS_PLATFORM_NAME STREQUAL "x64")
			# Check the toolset version for MSVC 2019
			set(GENERATOR_SHORT_NAME "msvc20${_MSVC_VERSION}_64")
		endif()
	endif()
endmacro(setup_generator_short_name)
