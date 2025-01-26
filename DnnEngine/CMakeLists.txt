cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(DnnEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE DNN_ENGINE_SOURCES src/*.cpp)

add_library(
    DnnEngine
    ${DNN_ENGINE_SOURCES}
)

target_link_libraries(DnnEngine)
target_precompile_headers(DnnEngine PRIVATE ../pch/pch.hxx)
target_include_directories(DnnEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")