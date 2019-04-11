cmake_minimum_required(VERSION 2.8)
project(jit CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(jit jit.cpp jit.h my_function.h)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -pedantic ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")

