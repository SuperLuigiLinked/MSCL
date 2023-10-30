# @file CMakeLists.txt

cmake_minimum_required(VERSION 3.25)
project(mscl LANGUAGES C CXX)

set(mscl_cflags
    PRIVATE
        "-Weverything"
        "-Wno-c++98-compat"
        "-Wno-c++98-compat-pedantic"
        "-Wno-declaration-after-statement"
        "-Wno-unsafe-buffer-usage"
        "-Wno-unused-macros"
)

add_subdirectory(mscl)
add_subdirectory(mscl_player)
add_subdirectory(mscl_demo)
