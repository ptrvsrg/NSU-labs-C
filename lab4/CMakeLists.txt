cmake_minimum_required(VERSION 3.5.1)
project(lab4 C)

set(SRC 
    src/calc.c
    src/calc.h
    src/error.c
    src/error.h
    src/input.c
    src/input.h
    src/stack.c
    src/stack.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
