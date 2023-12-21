#pragma once

#include "Block.h"
#include <vector>
namespace Leaf::Allocator {
    class Mallocator {
    public:
        Block Allocate(size_t size);
        void Realloc(Block& block, size_t size);
        void Deallocate(Block block);
        void DeallocateAll();
        bool Owns(Block block);

    private:
        std::vector<void *> m_allocated;
    };
}// namespace Leaf::Allocator