cmake_minimum_required(VERSION 3.14)
project(Player C)

set(CMAKE_C_STANDARD 11)
file(GLOB libsoundio.2.dylib)
add_executable(Player main.c)
