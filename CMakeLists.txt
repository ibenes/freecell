cmake_minimum_required (VERSION 3.16)

project(freecell CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE vsrc "*.cc")
file(GLOB_RECURSE vhead "*.h")

add_executable ("${PROJECT_NAME}" "${vsrc}" "${vhead}")

add_subdirectory(test)