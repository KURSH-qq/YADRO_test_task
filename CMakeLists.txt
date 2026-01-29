cmake_minimum_required(VERSION 3.10)
project(test_task)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES sample/solution.cpp)

file(GLOB_RECURSE SRC_FILES "src/*.cpp*")

add_executable(${PROJECT_NAME} ${SOURCES} ${SRC_FILES})
target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall
    -Wextra
    -Werror
    -pedantic
)
target_include_directories(${PROJECT_NAME} PRIVATE include)