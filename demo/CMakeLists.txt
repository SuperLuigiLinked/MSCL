# @file demo/CMakeLists.txt

# ================================================================================================================================

include(FetchContent)

FetchContent_Declare(PGE
    GIT_REPOSITORY "https://github.com/OneLoneCoder/olcPixelGameEngine"
    GIT_TAG "v2.23"
)
FetchContent_MakeAvailable(PGE)
FetchContent_GetProperties(PGE SOURCE_DIR PGE_SOURCE_DIR)

add_library(olc_PGE INTERFACE "${PGE_SOURCE_DIR}/olcPixelGameEngine.h")
add_library(olc::PGE ALIAS olc_PGE)

target_include_directories(olc_PGE INTERFACE "${PGE_SOURCE_DIR}/")

# ================================================================================================================================

add_executable(mscl_demo WIN32 MACOSX_BUNDLE)
add_executable(mscl::demo ALIAS mscl_demo)

target_include_directories(mscl_demo PUBLIC "include/")
target_sources(mscl_demo
    PRIVATE
        "include/utils.h"
        "include/player.hpp"
        "src/main.cpp"
        "src/player_xaudio2.cpp"
)
target_link_libraries(mscl_demo mscl::mscl olc::PGE)

target_compile_features(mscl_demo PRIVATE cxx_std_23)

target_compile_options(mscl_demo
    PRIVATE
        "-Weverything"
        "-Wno-c++98-compat"
        "-Wno-c++98-compat-pedantic"
        "-Wno-old-style-cast"
        "-Wno-declaration-after-statement"
        "-Wno-unsafe-buffer-usage"
        "-Wno-unused-macros"
        "-Wno-float-equal"
)

# ================================================================================================================================
