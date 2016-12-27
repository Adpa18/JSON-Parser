cmake_minimum_required(VERSION 3.6)
project(JSONParser)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

file(GLOB SOURCE_FILES *.cpp *.hpp)
add_executable(JSONParser ${SOURCE_FILES})