cmake_minimum_required(VERSION 3.13)

project(shell-starter-cpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp src/*.h)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

add_executable(shell ${SOURCE_FILES})

target_include_directories(shell PRIVATE 
    src
    src/include
    src/utils/include
    src/commands/include
    src/internal/service/include
)

target_link_libraries(shell PRIVATE readline)
