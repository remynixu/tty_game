cmake_minimum_required(VERSION 3.10)
project(tty_game C)

set(CMAKE_BINARY_DIR "./build")
set(CMAKE_C_STANDARD 90)
# some things are just extra sensitive, this is
# one of them. cant even handle a newline...
set(CMAKE_C_FLAGS
	"-Wall -Wextra -Wpedantic -fno-builtin")
set(CMAKE_EXE_LINKER_FLAGS 
	"${CMAKE_EXE_LINKER_FLAGS} -lportaudio -lm")

include(config.cmake)

message("> processing config.cmake")
if(COLORMODE_BASIC)
	add_definitions( -D__BASICCLR)
	message("> __BASICCLR defined")
elseif(COLORMODE_NONE)
	add_definitions( -D__NOCLR)
	message("> __NOCLR defined")
else()
	message("> COLORMODE error")
endif()

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(tty_game ${SOURCES})
