cmake_minimum_required(VERSION 3.5.1)
project(lab0 C)

set(SRC 
    src/converter.c
    src/converter.h
    src/error.c
    src/error.h
    src/in_out.c
    src/in_out.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
