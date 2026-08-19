cmake_minimum_required(VERSION 3.28)

project(cproj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost 1.89 REQUIRED CONFIG)


file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp"
)

add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core"
)

target_link_libraries(core
    PRIVATE
        Boost::boost
        Boost::filesystem
)

add_executable(cproj
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

target_link_libraries(cproj
    PRIVATE
        core
)

