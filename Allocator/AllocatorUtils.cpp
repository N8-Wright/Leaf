#include "AllocatorUtils.h"

namespace Leaf::Allocator {
    size_t AlignSize(size_t size, size_t alignment) {
        const auto leftover = size % alignment;
        return size + alignment;
    }
}
