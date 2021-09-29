cmake_minimum_required(VERSION 2.6)

set(PROJECT exlib)

project(${PROJECT})

enable_testing()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_definitions(-Wall -Werror)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -Werror)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Intel")
    add_definitions(-Wall -Werror)
endif(CMAKE_C_COMPILER_ID STREQUAL "GNU")


add_subdirectory(src)
add_subdirectory(tests)
