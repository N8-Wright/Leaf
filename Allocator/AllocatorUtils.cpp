#include "AllocatorUtils.h"

namespace Leaf::Allocator {
    size_t AlignSize(size_t size, size_t alignment) {
        const auto leftover = size % alignment;
        if (leftover != 0) {
            return size + (alignment - leftover);
        }
        else
        {
            return size;
        }
    }
}
