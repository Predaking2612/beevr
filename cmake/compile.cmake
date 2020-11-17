function(project_warnings project_name)
	set (CLANG_WARNINGS 
			-Wall
			-Wextra
			-Wshadow
			-Wcast-align
			-Wpedantic
			-Wconversion
			-Wnull-dereference
			-Wsign-conversion
			-Wunused
			-Wdouble-promotion)

	set (GCC_WARNINGS
			${CLANG_WARNINGS}
			-Wuseless-cast
			-Wlogical-op
			-Wduplicated-cond)

	set (DEBUG_FLAGS 
			-g
			-fstack-protector-strong
			-foptimize-strlen
			-fpic)

	if (${CMAKE_C_COMPILER_ID} MATCHES ".*CLANG")
		set (PROJECT_WARNINGS ${CLANG_WARNINGS})
	elseif (${CMAKE_C_COMPILER_ID} MATCHES  "GNU")
		message ("Setting GNU compiler warning flags")
		set (PROJECT_WARNINGS ${GCC_WARNINGS})
	endif()

	if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
	  set (${PROJECT_WARNINGS} "${DEBUG_FLAGS}")
	  target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
	else() 
	  target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})
	endif()

	# optimize_build(${project_name})
endfunction()
