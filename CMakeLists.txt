cmake_minimum_required(VERSION 3.10)
project(tty_game C)

include(config.cmake)

set(CMAKE_BINARY_DIR "./build")
set(CMAKE_SOURCE_DIR "./")
set(CMAKE_INSTALL_PREFIX "./bin")

message("> processing config.cmake\n")
if(COLORMODE_BASIC)
	add_definitions(__BASICCLR)
	message("> __BASICCLR defined\n")
elseif(COLORMODE_NONE)
	add_definitions(__NOCLR)
	message("> __NOCLR defined\n")
else()
	message("> COLORMODE error\n")
endif()

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")

file(GLOB_RECURSE SOURCES "*.c")
file(GLOB_RECURSE HEADERS "*.h")
add_executable(tty_game ${SOURCES} ${HEADERS})
