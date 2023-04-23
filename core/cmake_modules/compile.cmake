macro(cpp_compile_options_fixes)
	if(MSVC)
		# fix __cplusplus macro for MSVC
		add_compile_options(
			"/Zc:__cplusplus"
			# "/std:c++latest"
		)
	endif()
endmacro(cpp_compile_options_fixes)
