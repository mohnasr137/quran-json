cmake_minimum_required(VERSION 3.16)
project(quran_json VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(quran_json main.cpp)

# Header include paths
target_include_directories(quran_json PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Compiler warning flags
if(MSVC)
    target_compile_options(quran_json PRIVATE /W4)
else()
    target_compile_options(quran_json PRIVATE -Wall -Wextra)
endif()
