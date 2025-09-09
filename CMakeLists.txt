cmake_minimum_required(VERSION 3.10)
project(tty_game C)

set(CMAKE_BINARY_DIR "./build")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lm")

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(tty_game ${SOURCES})
