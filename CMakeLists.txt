cmake_minimum_required(VERSION 2.8)
add_subdirectory(src)
project(test)
add_executable(Main
  ${PROJECT_HOME}/src/main.cpp
 )