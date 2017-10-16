cmake_minimum_required(VERSION 3.8)
project(Paskal_Function_Header_lib)

set(SOURCES lexical_analyzer.cpp parser.cpp parse_exception.h)

add_library(Paskal_Function_Header_lib ${SOURCES})
