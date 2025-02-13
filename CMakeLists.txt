cmake_minimum_required(VERSION 3.10)
project(tty_game C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -Wextra")

file(GLOB_RECURSE SOURCES "*.c")
add_executable(tty_game ${SOURCES})
