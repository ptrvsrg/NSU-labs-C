cmake_minimum_required(VERSION 3.5.1)
project(lab11 C)

set(SRC 
    src/error.c
    src/error.h
    src/knapsack.c
    src/knapsack.h
    src/subject.c
    src/subject.h
    src/table.c
    src/table.h
    src/vector.c
    src/vector.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
