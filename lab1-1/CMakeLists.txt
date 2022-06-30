cmake_minimum_required(VERSION 3.5.1)
project(lab1-1 C)

set(SRC 
    src/circular_list.c
    src/circular_list.h
    src/error.c
    src/error.h
    src/hash.c
    src/hash.h
    src/rabin_karp.c
    src/rabin_karp.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
