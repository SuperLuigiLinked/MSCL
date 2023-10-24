# @file demo/CMakeLists.txt

add_executable(mscl_demo WIN32 MACOSX_BUNDLE)
add_executable(mscl::demo ALIAS mscl_demo)

target_sources(mscl_demo PRIVATE "src/demo.cpp")
target_link_libraries(mscl_demo mscl::mscl)

target_compile_features(mscl_demo PRIVATE cxx_std_23)

target_compile_options(mscl_demo
    PRIVATE
        "-Weverything"
)
