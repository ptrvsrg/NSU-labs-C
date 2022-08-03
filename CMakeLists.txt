cmake_minimum_required(VERSION 3.5.1)
project(all_lab C)

file(GLOB LABS "lab*")

if(WIN32)
    set(EXE ".exe")
endif()

enable_testing()

foreach(DIR ${LABS})
    string(REPLACE "${CMAKE_HOME_DIRECTORY}/" "" LAB ${DIR})
    message(STATUS "Adding subdirectory ${LAB}")
    add_subdirectory(${LAB})
endforeach()