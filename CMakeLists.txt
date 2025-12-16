cmake_minimum_required(VERSION 3.16)
project(zrite)

project(zrite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(zrite
    main.cpp
)

target_link_libraries(zrite sfml-graphics sfml-window sfml-system sfml-audio)

