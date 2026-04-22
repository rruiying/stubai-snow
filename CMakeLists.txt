cmake_minimum_required(VERSION 3.22)

project(stubai_snow
    VERSION 0.1.0
    DESCRIPTION "A simple snowy day redering of Stubai Gletscher Gamsgarten Bergstation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(stubai_snow
    src/app/main.cpp
)