add_library(Allocator
        Block.h
        Block.cpp
        Mallocator.h
        Mallocator.cpp
        StackAllocator.h
        AllocatorUtils.h
        AllocatorUtils.cpp)

target_include_directories(Allocator PUBLIC .)