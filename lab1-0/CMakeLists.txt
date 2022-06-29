cmake_minimum_required(VERSION 3.5.1)
project(lab1-0 C)

set(SRC 
    src/boyer_moore.c
    src/boyer_moore.h
    src/error.c
    src/error.h
    src/ring_array.c
    src/ring_array.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
