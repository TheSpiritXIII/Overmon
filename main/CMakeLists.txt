cmake_minimum_required (VERSION 3.0)

project(Overmon)
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(Tutorial_VERSION_MAJOR 0)
set(Tutorial_VERSION_MINOR 1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_LIST source/*.cpp source/Character/* source/Sprite/* source/External/* source/Util/*)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
