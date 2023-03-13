cmake_minimum_required(VERSION 3.5)

project(Onzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

