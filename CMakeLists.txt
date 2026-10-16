cmake_minimum_required(VERSION 3.24)
project(gta5_optimizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus)
else()
    add_compile_options(-Wall -Wextra)
endif()

add_subdirectory(src)
add_subdirectory(tests)

option(GTA5OPT_BUILD_INJECTOR "Build the standalone injector CLI" ON)
if(GTA5OPT_BUILD_INJECTOR)
    add_subdirectory(cmd/injector)
endif()