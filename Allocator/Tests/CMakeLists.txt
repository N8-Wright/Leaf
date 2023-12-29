add_executable(AllocatorTests AllocatorUtilsTests.cpp)
target_link_libraries(AllocatorTests PRIVATE Catch2::Catch2WithMain Allocator)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(
            CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -Werror -fsanitize=undefined -fsanitize=address"
    )
    target_link_options(AllocatorTests
            BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
    )
endif()

include(Catch)
catch_discover_tests(AllocatorTests)
