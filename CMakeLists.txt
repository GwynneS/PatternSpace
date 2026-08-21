cmake_minimum_required(VERSION 3.16)
project(PatternSpace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(patternspace
    main.cpp
    geometry.cpp
    pattern.cpp
    similarity.cpp
    svg.cpp
)

if(MSVC)
    target_compile_options(patternspace PRIVATE /W4)
else()
    target_compile_options(patternspace PRIVATE -Wall -Wextra -Wpedantic)
endif()
