cmake_minimum_required(VERSION 3.17)
project(rotateImg C)

set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES main.c view-header/bmp.c util.c bmp.h image.c bmp.c image.h)
add_executable(rotateImg ${SOURCE_FILES})