cmake_minimum_required(VERSION 3.8)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-O2 -Wall -Wextra -Werror")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

find_library(GRAPHVISLIBS NAMES libcgraph.so.6.0.0 libgvc.so.6.0.0 libcdt.so.5.0.0)

set(SOURCE_FILES main.cpp visualizator.cpp)

add_executable(Lab2 ${SOURCE_FILES})

include_directories(tests)

add_subdirectory(paskal_function_header)

target_link_libraries(Lab2 Paskal_Function_Header_lib ${GRAPHVISLIBS} gvc cgraph cdt)

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tests/
        ${CMAKE_CURRENT_BINARY_DIR}/tests/)
