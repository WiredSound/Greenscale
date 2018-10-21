cmake_minimum_required (VERSION 3.1)

project (Greenscale)

include_directories ("include/")
include_directories ("${PROJECT_BINARY_DIR}")

add_definitions (-DDEBUG)
set (CMAKE_CXX_STANDARD 14)

set (EXECUTABLE_NAME "Greenscale")
file (GLOB_RECURSE SRC "src/*.cpp")
add_executable (${EXECUTABLE_NAME} ${SRC})

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package (SFML 2 REQUIRED system graphics window)
if (SFML_FOUND)
  include_directories (${SFML_INCLUDE_DIR})
  target_link_libraries (${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
