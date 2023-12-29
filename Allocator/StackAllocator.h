#pragma once
#include "AllocatorUtils.h"
#include "Block.h"
#include <array>
#include <cstdint>
namespace Leaf::Allocator {
    template<size_t StackSize = 16384, size_t Alignment = 8>
    class StackAllocator {
    public:
        Block Allocate(size_t size) {
            if (m_head > StackSize) {
                return {};
            }

            size = AlignSize(size, Alignment);
            Block block(&m_stack[m_head], size);
            m_head += size;
            return block;
        }

        void Realloc(Block &block, size_t size) {
        }

        void Deallocate(Block block) {
            (void) block;
        }

        void DeallocateAll() {
            m_head = 0;
        }

        bool Owns(Block block) {
            return block.Ptr >= &m_stack[0] && block.Ptr <= &m_stack[StackSize - 1];
        }

    private:
        std::array<uint8_t, StackSize> m_stack;
        std::ptrdiff_t m_head = 0;
    };
}// namespace Leaf::Allocator
