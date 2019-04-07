if(NOT EocKrnln_FOUND)
	if(NOT DEFINED EOC_HOME)
		set(EOC_HOME $ENV{EOC_HOME})
	endif()
	include(${EOC_HOME}/EocBuildHelper.cmake)
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_BINARY_DIR}/EocKrnln)
	
	include(${EOC_LIBS_DIRS}/system/config.cmake)

	set(EocKrnln_FOUND True)
	set(EocKrnln_INCLUDE_DIRS ${EocSystem_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/src)
	set(EocKrnln_LIBRARIES ${EocSystem_LIBRARIES} EocKrnln)
endif()