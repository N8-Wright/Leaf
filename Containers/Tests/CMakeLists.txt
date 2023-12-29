add_executable(ContainerTests VectorTests.cpp)
target_link_libraries(ContainerTests PRIVATE Catch2::Catch2WithMain Containers)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Werror -fsanitize=undefined -fsanitize=address"
    )
    target_link_options(ContainerTests
        BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
    )
endif()

include(Catch)
catch_discover_tests(ContainerTests)
