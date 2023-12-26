#include <catch2/catch_test_macros.hpp>
#include "Vector.h"
#include <sstream>
using namespace Leaf::Containers;
TEST_CASE("Integers can be pushed", "[Vector]") {
    Vector<int> integers;
    for (int i = 0; i < 123; i++) {
        integers.Push(i);
        integers.Push(99);
    }

    REQUIRE(integers.Length() == 123 * 2);
}

TEST_CASE("Integers can be inserted", "[Vector]") {
    Vector<int> integers;
    int i = 1;
    integers.Insert(i++, 0);
    integers.Insert(i++, 0);
    integers.Insert(i++, 0);
    integers.Insert(i, 0);

    REQUIRE(integers.Length() == 4);
    REQUIRE(integers[0] == 4);
    REQUIRE(integers[1] == 3);
    REQUIRE(integers[2] == 2);
    REQUIRE(integers[3] == 1);
}

TEST_CASE("Unique pointer can be pushed", "[Vector]") {
    Vector<std::unique_ptr<int>> integers;
    for (int i = 0; i < 123; i++) {
        auto value = std::make_unique<int>(i);
        integers.Push(std::move(value));
    }

    for (int i = 0; i < 123; i++) {
        REQUIRE(*integers[i] == i);
    }

    REQUIRE(integers.Length() == 123);
}

TEST_CASE("Unique pointer can be emplaced", "[Vector]") {
    Vector<std::unique_ptr<int>> integers;
    for (int i = 0; i < 123; i++) {
        integers.Emplace(std::make_unique<int>(i));
    }

    for (int i = 0; i < 123; i++) {
        REQUIRE(*integers[i] == i);
    }

    REQUIRE(integers.Length() == 123);
}

TEST_CASE("String can be pushed", "[Vector]") {
    Vector<std::string> strings;
    for (int i = 0; i < 999; i++) {
        std::stringstream ss;
        ss << "Hello world! " << i;
        strings.Push(ss.str());
    }

    for (int i = 0; i < 999; i++) {
        std::stringstream ss;
        ss << "Hello world! " << i;

        REQUIRE(ss.str() == strings[i]);
    }

    REQUIRE(strings.Length() == 999);
}

TEST_CASE("String can be emplaced", "[Vector]") {
    Vector<std::string> strings;
    strings.Emplace("12345");
    strings.Emplace("67891");
    strings.Emplace("ABCDE");

    REQUIRE(strings[0] == "12345");
    REQUIRE(strings[1] == "67891");
    REQUIRE(strings[2] == "ABCDE");
    REQUIRE(strings.Length() == 3);
}

TEST_CASE("String can be inserted at beginning", "[Vector]") {
    Vector<std::string> strings;
    strings.Insert("1", 0);
    REQUIRE(strings[0] == "1");

    strings.Insert("2", 0);
    REQUIRE(strings[1] == "1");
    REQUIRE(strings[0] == "2");

    strings.Insert("3", 0);
    REQUIRE(strings[2] == "1");
    REQUIRE(strings[1] == "2");
    REQUIRE(strings[0] == "3");

    strings.Insert("4", 0);
    REQUIRE(strings[0] == "4");
    REQUIRE(strings[1] == "3");
    REQUIRE(strings[2] == "2");
    REQUIRE(strings[3] == "1");
}

TEST_CASE("String can be inserted at end", "[Vector]") {
    Vector<std::string> strings;
    strings.Insert("1", 0);
    REQUIRE(strings[0] == "1");

    strings.Insert("2", 1);
    REQUIRE(strings[0] == "1");
    REQUIRE(strings[1] == "2");

    strings.Insert("3", 2);
    REQUIRE(strings[0] == "1");
    REQUIRE(strings[1] == "2");
    REQUIRE(strings[2] == "3");
}

TEST_CASE("String can be inserted in random order", "[Vector]") {
    Vector<std::string> strings;
    strings.Push("1");
    strings.Push("3");
    strings.Push("5");

    strings.Insert("4", 2);
    strings.Insert("2", 1);

    REQUIRE(strings[0] == "1");
    REQUIRE(strings[1] == "2");
    REQUIRE(strings[2] == "3");
    REQUIRE(strings[3] == "4");
    REQUIRE(strings[4] == "5");
}
