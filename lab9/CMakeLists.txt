cmake_minimum_required(VERSION 3.5.1)
project(lab9 C)

set(SRC 
    src/dijkstra.c
    src/dijkstra.h
    src/error.c
    src/error.h
    src/graph.c
    src/graph.h
    src/heap.c
    src/heap.h
    src/matrix.c
    src/matrix.h
    src/output.c
    src/output.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
