# @file mscl/CMakeLists.txt

add_library(mscl_mscl)
add_library(mscl::mscl ALIAS mscl_mscl)

target_include_directories(mscl_mscl PUBLIC "include/")
target_sources(mscl_mscl PUBLIC "include/mscl.h" "src/mscl.c")

target_compile_features(mscl_mscl PRIVATE c_std_23)

target_compile_options(mscl_mscl
    PRIVATE
        "-Weverything"
)
