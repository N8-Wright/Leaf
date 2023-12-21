add_library(Containers Vector.h Dummy.cpp)
target_link_libraries(Containers Allocator)
target_include_directories(Containers PUBLIC .)
add_subdirectory(Tests)