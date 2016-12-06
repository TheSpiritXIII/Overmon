cmake_minimum_required(VERSION 3.1)

project(Overmon)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/source/)

file(GLOB_RECURSE SRC_LIST source/*.cpp source/*.hpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Detect and add SFML 2.x.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
