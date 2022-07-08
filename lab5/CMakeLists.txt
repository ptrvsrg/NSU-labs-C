cmake_minimum_required(VERSION 3.5.1)
project(lab5 C)

set(SRC 
    src/bitline.c
    src/bitline.h
    src/code_table.c
    src/code_table.h
    src/decode.c
    src/decode.h
    src/encode.c
    src/encode.h
    src/error.c
    src/error.h
    src/huffman_tree.c
    src/huffman_tree.h
    src/priority_list.c
    src/priority_list.h
    src/stack.c
    src/stack.h
    src/stream.c
    src/stream.h
    src/tree.c
    src/tree.h
    src/main.c
    )

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
