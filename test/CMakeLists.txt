cmake_minimum_required (VERSION 3.8)

project (freecell_test CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE tsrc "src/*.cc")
file(GLOB_RECURSE thead "include/*.h")

add_executable("${PROJECT_NAME}" "${vsrc}" "${vhead}")

target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")