add_library(Allocator Block.h Block.cpp
        Mallocator.h
        Mallocator.cpp)

target_include_directories(Allocator PUBLIC .)