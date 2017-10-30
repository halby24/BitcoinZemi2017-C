cmake_minimum_required(VERSION 3.8)
project(bitcoin)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

# load the module to use pkg-config
find_package(PkgConfig)

# search library with pkg-config and name its results "LIB"
pkg_check_modules(LIB REQUIRED libbitcoin)

# use the variable <RESULTNAME>_INCLUDE_DIRS to get include paths
include_directories(${LIB_INCLUDE_DIRS})

add_executable(bitcoin ${SOURCE_FILES})
add_executable(pubkey pubkey.cpp)
add_executable(vanity vanity.cpp)

target_link_libraries(bitcoin ${LIB_LIBRARIES})
target_link_libraries(pubkey ${LIB_LIBRARIES})
target_link_libraries(vanity ${LIB_LIBRARIES})