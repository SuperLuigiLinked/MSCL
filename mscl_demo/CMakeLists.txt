# @file mscl_demo/CMakeLists.txt

# ================================================================================================================================

add_executable(mscl_demo WIN32 MACOSX_BUNDLE)
add_executable(mscl::demo ALIAS mscl_demo)

target_include_directories(mscl_demo PUBLIC "include/")
target_sources(mscl_demo
    PRIVATE
        "src/main.cpp"
        "include/instruments.hpp"
        "include/songs.hpp"
)
target_link_libraries(mscl_demo mscl::mscl mscl::player)

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
