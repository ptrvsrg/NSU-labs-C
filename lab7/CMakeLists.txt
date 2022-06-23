cmake_minimum_required(VERSION 3.5.1)
project(lab7 C)

set(SRC 
    src/error.c
    src/error.h
    src/graph.c
    src/graph.h
    src/matrix.c
    src/matrix.h
    src/stack.c
    src/stack.h
    src/topsort.c
    src/topsort.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
