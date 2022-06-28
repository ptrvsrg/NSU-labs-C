cmake_minimum_required(VERSION 3.5.1)
project(lab2 C)

set(SRC 
    src/error.c
    src/error.h
    src/inout.c
    src/inout.h
    src/narayana.c
    src/narayana.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
