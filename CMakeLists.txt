cmake_minimum_required(VERSION 3.23.2)
project(arena-simulator)

include_directories(include)

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(arena-simulator PUBLIC cxx_std_17)