cmake_minimum_required(VERSION 3.14)

project(sorting-algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

include_directories("${PROJECT_SOURCE_DIR}/inc")

add_executable(sorting-algorithms main.cpp)
