#include "Block.h"

namespace Leaf::Allocator {
    Block::Block()
            : Ptr(nullptr), Size(0) {
    }

    Block::Block(void *ptr, size_t size)
        : Ptr(ptr), Size(size) {
    }
}