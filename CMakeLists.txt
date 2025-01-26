cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(TestCase LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

set(THIRD_PARTY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty")


set(OPENCV_VERSION 4.10)
find_package(OpenCV ${OPENCV_VERSION} REQUIRED PATHS "${THIRD_PARTY_PATH}/OpenCV-${OPENCV_VERSION}")
if(NOT OpenCV_FOUND)
	message(ERROR "OpenCV could not found")
	return()
endif()

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(./DnnEngine DnnEngine_build)
set(MODEL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/model/")
set(DATA_PATH "${CMAKE_CURRENT_SOURCE_DIR}/data/")
add_definitions(-DMODEL_PATH="${MODEL_PATH}")
add_definitions(-DDATA_PATH="${DATA_PATH}")

macro(add_example example_name)
	add_executable(${example_name} ${example_name}.cpp)
	target_precompile_headers(${example_name} PRIVATE ./pch/pch.hxx)
	target_link_libraries(${example_name} PRIVATE DnnEngine pthread ${OpenCV_LIBS})
endmacro()

add_example(TestCase)