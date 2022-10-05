cmake_minimum_required (VERSION 3.16)

project(freecell CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE vsrc "src/*.cc")
file(GLOB_RECURSE vhead "include/*.h")

add_executable ("${PROJECT_NAME}" "${vsrc}" "${vhead}")
target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(test)