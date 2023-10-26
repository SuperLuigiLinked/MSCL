# @file mscl_player/CMakeLists.txt

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

add_library(mscl_player)
add_library(mscl::player ALIAS mscl_player)

target_include_directories(mscl_player PUBLIC "include/")
target_sources(mscl_player
    PRIVATE
        "src/gui.cpp"
        "src/xaudio2.cpp"
        "include/mscl_player.hpp"
)
target_link_libraries(mscl_player mscl::mscl olc::PGE)

target_compile_features(mscl_player PRIVATE cxx_std_23)

target_compile_options(mscl_player
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
