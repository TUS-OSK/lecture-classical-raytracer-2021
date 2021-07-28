add_executable(test test.cpp)
target_compile_feature(test PRIVATE cxx_std_17)
target_include_directories(test PRIVATE src)