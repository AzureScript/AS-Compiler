cmake_minimum_required(VERSION 3.12)
project(AzureScript)

set(CMAKE_CXX_STANDARD 14)

add_executable(AzureScript src/main.cpp src/lex_analysis.cpp src/lex_analysis.h src/lex_private.h src/common.h)