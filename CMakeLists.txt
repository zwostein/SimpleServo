cmake_minimum_required( VERSION 2.8 )
project( SimpleServo )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -std=c99" )

include( ExternalProject )
ExternalProject_Add(
	external_pigpio
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/pigpio"
	DOWNLOAD_COMMAND ""
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND make x_pigpio
	INSTALL_COMMAND ""
	TEST_COMMAND ""
	BUILD_IN_SOURCE 1
)

link_directories( "${CMAKE_SOURCE_DIR}/external/pigpio" )
include_directories( "${CMAKE_SOURCE_DIR}/external/pigpio" )

set( EXECUTABLE_NAME "simpleServo" )
add_executable( ${EXECUTABLE_NAME}
	src/main.c
)
target_link_libraries( ${EXECUTABLE_NAME} pigpio pthread rt )
