cmake_minimum_required(VERSION 3.5.1)
project(lab1-0 C)

set(SRC 
    src/boyer_moore.c
    src/error.h
    src/circular_list.c
    src/circular_list.h
    src/boyer_moore.h
    src/error.c
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
