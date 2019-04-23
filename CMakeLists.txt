cmake_minimum_required(VERSION 3.13)
project(Temp)

set(CMAKE_CXX_STANDARD 14)





set(CMAKE_CXX_FLAGS_RELEASE "-O3")
find_package(benchmark CONFIG REQUIRED)
add_executable(Temp main.cpp)

target_link_libraries(Temp PRIVATE benchmark::benchmark benchmark::benchmark_main)