cmake_minimum_required(VERSION 3.5.1)
project(lab10 C)

set(SRC
    src/andrew.c
    src/andrew.h
    src/error.c
    src/error.h
    src/point.c
    src/point.h
    src/stack.c
    src/stack.h
    src/vector.c
    src/vector.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
