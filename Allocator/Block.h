#pragma once
#include <cstddef>
namespace Leaf::Allocator {
    class Block {
    public:
        Block();
        Block(void *ptr, size_t size);
        void *Ptr;
        size_t Size;
    };
}