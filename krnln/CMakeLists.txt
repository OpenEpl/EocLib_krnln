cmake_minimum_required(VERSION 3.8)

if(NOT DEFINED EOC_HOME)
	set(EOC_HOME $ENV{EOC_HOME})
endif()
include(${EOC_HOME}/EocBuildHelper.cmake)

project(EocKrnln)
aux_source_directory(${EocKrnln_SOURCE_DIR}/src/e/lib/krnln EocKrnln_DIR_SRCS)
add_library(EocKrnln ${EocKrnln_DIR_SRCS})
set_property(TARGET EocKrnln PROPERTY CXX_STANDARD 17)
set_property(TARGET EocKrnln PROPERTY CXX_STANDARD_REQUIRED ON)

include(${EOC_LIBS_DIRS}/system/config.cmake)
target_include_directories(EocKrnln PRIVATE ${EocSystem_INCLUDE_DIRS})
target_link_libraries(EocKrnln ${EocSystem_LIBRARIES})