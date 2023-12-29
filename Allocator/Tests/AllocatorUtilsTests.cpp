#include "AllocatorUtils.h"
#include <catch2/catch_test_macros.hpp>

using namespace Leaf::Allocator;
TEST_CASE("Align by 8 bytes. Value is zero", "[AllocatorUtils]") {
    REQUIRE(AlignSize(0, 8) == 0);
}

TEST_CASE("Align by 8 bytes. Values are less than 8", "[AllocatorUtils]") {
    for (size_t i = 1; i <= 8; i++) {
        const auto aligned = AlignSize(i, 8);
        REQUIRE(aligned == 8);
    }
}

TEST_CASE("Align by 8 bytes. Values are greater than 8", "[AllocatorUtils]") {
    for (size_t i = 9; i <= 16; i++) {
        const auto aligned = AlignSize(i, 8);
        REQUIRE(aligned == 16);
    }
}

TEST_CASE("Align by 16 bytes. Values are less than 16", "[AllocatorUtils]") {
    for (size_t i = 1; i <= 16; i++) {
        const auto aligned = AlignSize(i, 16);
        REQUIRE(aligned == 16);
    }
}

TEST_CASE("Align by 16 bytes. Values are greater than 16", "[AllocatorUtils]") {
    for (size_t i = 17; i <= 32; i++) {
        const auto aligned = AlignSize(i, 16);
        REQUIRE(aligned == 32);
    }
}
