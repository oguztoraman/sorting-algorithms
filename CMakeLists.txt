# SPDX-FileCopyrightText: Copyright (c) 2022-2024 Oğuz Toraman <oguz.toraman@tutanota.com>
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.14)

project(sorting-algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

find_package(Boost COMPONENTS program_options REQUIRED)

add_compile_options(-Wall -Wextra -Wfatal-errors)

include_directories("${PROJECT_SOURCE_DIR}/inc" "${PROJECT_SOURCE_DIR}" ${Boost_INCLUDE_DIR})

add_executable(sorting-algorithms main.cpp)

target_link_libraries(sorting-algorithms ${Boost_LIBRARIES})
