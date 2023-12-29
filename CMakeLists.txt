cmake_minimum_required(VERSION 3.27)
project(Leaf)

Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Allocator)
add_subdirectory(Containers)
add_executable(Test main.cpp)
target_link_libraries(Test Containers)