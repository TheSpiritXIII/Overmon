cmake_minimum_required(VERSION 3.1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../binary)

project(OvermonDemo)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../core/Overmon/ ${CMAKE_CURRENT_SOURCE_DIR}/../core/)

add_executable(${PROJECT_NAME} Main.cpp)
if(WIN32)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../../binary/OvermonCore.lib)
else()
	target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../../binary/libOvermonCore.a)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../core/cmake ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

if(NOT MSVC)
	target_link_libraries(${PROJECT_NAME} stdc++fs)
endif()
