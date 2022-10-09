cmake_minimum_required (VERSION 3.16)

project(freecell CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE vsrc "*.cc")
file(GLOB_RECURSE vhead "*.h")

list(FILTER vsrc EXCLUDE REGEX "test")
list(FILTER vsrc EXCLUDE REGEX "fc-sui")

add_library ("${PROJECT_NAME}lib" "${vsrc}" "${vhead}")

add_executable ("${PROJECT_NAME}" "fc-sui.cc" "${vhead}")
target_link_libraries("${PROJECT_NAME}" PRIVATE "${PROJECT_NAME}lib") # mymod uses symbols from myexe

add_executable("${PROJECT_NAME}_test" "test.cc" "test-main.cc")
target_link_libraries("${PROJECT_NAME}_test" PRIVATE "${PROJECT_NAME}lib") # mymod uses symbols from myexe

