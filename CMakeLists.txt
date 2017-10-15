cmake_minimum_required(VERSION 3.8)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-O2 -Wall -Wextra -Werror")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

set(graphviz_cgraph "/usr/lib/libcgraph.so.6.0.0")
set(graphviz_gvc "/usr/lib/libgvc.so.6.0.0")
set(grpahviz_cdt "/usr/lib/libcdt.so.5.0.0")

set(SOURCE_FILES main.cpp visualizator.cpp)

add_executable(Lab2 ${SOURCE_FILES})

add_subdirectory(paskal_function_header)

target_link_libraries(Lab2 Paskal_Function_Header_lib ${graphviz_cgraph} ${graphviz_gvc} ${grpahviz_cdt} gvc cgraph cdt)
