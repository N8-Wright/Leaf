#include "Mallocator.h"
#include <cstdlib>

namespace Leaf::Allocator {
    Block Mallocator::Allocate(size_t size) {
        auto ptr = malloc(size);
        if (ptr != nullptr) {
            m_allocated.push_back(ptr);
        }

        return { ptr, size };
    }

    void Mallocator::Realloc(Block& block, size_t size) {
        void* result = realloc(block.Ptr, size);
        if (result == nullptr) {
            Deallocate(block);
        }

        block.Ptr = result;
        block.Size = size;
    }

    void Mallocator::Deallocate(Block block) {
        m_allocated.erase(std::remove(m_allocated.begin(), m_allocated.end(), block.Ptr), m_allocated.end());
        free(block.Ptr);
    }

    void Mallocator::DeallocateAll() {
        for (const auto ptr : m_allocated) {
            free(ptr);
        }
    }

    bool Mallocator::Owns(Block block) {
        auto result = std::find(m_allocated.begin(), m_allocated.end(), block.Ptr);
        return result != std::end(m_allocated);
    }
}
