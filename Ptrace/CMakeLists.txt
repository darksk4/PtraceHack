cmake_minimum_required(VERSION 3.8)

add_executable(execute main.cpp)
target_compile_options(execute
    PRIVATE
        -std=c++11
)
