#include "StackAllocator.h"
#include <catch2/catch_test_macros.hpp>

using namespace Leaf::Allocator;
TEST_CASE("Stack allocator defaults", "[StackAllocator]") {
    StackAllocator<> allocator;
    const auto block = allocator.Allocate(1);
    REQUIRE(block.Size == 8);
}

TEST_CASE("Allocate more than stack allows", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;
    const auto block = allocator.Allocate(24);
    REQUIRE(block.Ptr == nullptr);
    REQUIRE(block.Size == 0);
}

TEST_CASE("Allocate the whole stack", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;
    const auto block = allocator.Allocate(16);
    REQUIRE(block.Ptr != nullptr);
    REQUIRE(block.Size == 16);
}

TEST_CASE("Allocate the whole stack because of alignment", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;
    const auto block = allocator.Allocate(14);
    REQUIRE(block.Ptr != nullptr);
    REQUIRE(block.Size == 16);
}

TEST_CASE("Allocate the whole stack then ask for more", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;
    const auto block = allocator.Allocate(16);
    REQUIRE(block.Ptr != nullptr);
    REQUIRE(block.Size == 16);

    const auto nextBlock = allocator.Allocate(1);
    REQUIRE(nextBlock.Ptr == nullptr);
    REQUIRE(nextBlock.Size == 0);
}

TEST_CASE("Allocate the whole stack in multiple blocks", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;
    const auto block1 = allocator.Allocate(1);
    const auto block2 = allocator.Allocate(1);
    REQUIRE(block1.Ptr != nullptr);
    REQUIRE(block2.Ptr != nullptr);
    REQUIRE(block1.Size == 8);
    REQUIRE(block2.Size == 8);
}

TEST_CASE("Deallocate most recently allocated. Can allocate that space again", "[StackAllocator]") {
    StackAllocator<32, 8> allocator;
    const auto block1 = allocator.Allocate(1);
    REQUIRE(block1.Ptr != nullptr);
    REQUIRE(block1.Size == 8);
    const auto expectedPtr = block1.Ptr;

    allocator.Deallocate(block1);
    const auto block1Reallocated = allocator.Allocate(2);
    REQUIRE(block1Reallocated.Ptr == expectedPtr);
}

TEST_CASE("Deallocate block. Cannot allocate space again", "[StackAllocator]") {
    StackAllocator<32, 8> allocator;
    const auto block1 = allocator.Allocate(1);
    REQUIRE(block1.Ptr != nullptr);
    REQUIRE(block1.Size == 8);

    const auto block2 = allocator.Allocate(2);
    REQUIRE(block2.Ptr != nullptr);
    REQUIRE(block2.Size == 8);

    allocator.Deallocate(block1);
    const auto block3 = allocator.Allocate(3);
    REQUIRE(block3.Ptr != block1.Ptr);
}

TEST_CASE("Deallocate all. Able to allocate new blocks", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;
    const auto block1 = allocator.Allocate(1);
    const auto block2 = allocator.Allocate(2);

    // Demonstrate that we cannot allocate more memory
    REQUIRE(allocator.Allocate(1).Ptr == nullptr);

    allocator.DeallocateAll();
    const auto block3 = allocator.Allocate(1);
    REQUIRE(block3.Ptr != nullptr);
    REQUIRE(block3.Size == 8);
}

TEST_CASE("Random ptr provided that allocator does not own", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;

    const Block block((void*)123, 9999);
    REQUIRE(allocator.Owns(block) == false);
}

TEST_CASE("Ptr that was allocated is owned by allocator", "[StackAllocator]") {
    StackAllocator<16, 8> allocator;
    const auto block1 = allocator.Allocate(1);
    const auto block2 = allocator.Allocate(2);

    REQUIRE(allocator.Owns(block1));
    REQUIRE(allocator.Owns(block2));
}
