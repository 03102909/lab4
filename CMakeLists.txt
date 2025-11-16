cmake_minimum_required(VERSION 3.20)
project(lab4 CXX)

set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-15")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE APPLE_SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${APPLE_SDK_PATH}")

add_compile_options(-fdiagnostics-color=always)

add_executable(main main.cpp
        Generator.cpp
        MyStruct.cpp
)

find_package(TBB REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(main PRIVATE
        Threads::Threads
        TBB::tbb
)