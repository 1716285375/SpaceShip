# 标题
cmake_minimum_required(VERSION 3.10.0)
project(SpaceShoot VERSION 0.1.0 LANGUAGES C CXX)

# 设置项目根目录
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# 设置SDL2库的根目录（根据你的实际路径修改）
set(SDL2_BASE_DIR    "${CMAKE_SOURCE_DIR}/thirdparty/SDL2")
message(STATUS "SDL2_BASE_DIR: ${SDL2_BASE_DIR}")
# 设置SDL2的CMake目录
set(SDL2_DIR "${SDL2_BASE_DIR}/cmake")
set(SDL2_image_DIR "${SDL2_BASE_DIR}/cmake")
set(SDL2_mixer_DIR "${SDL2_BASE_DIR}/cmake")
set(SDL2_ttf_DIR "${SDL2_BASE_DIR}/cmake")
message(STATUS "SDL2_DIR: ${SDL2_DIR}")

# 添加SDL2的头文件搜索路径
set(SDL2_INCLUDE_DIR "${SDL2_BASE_DIR}/include")
message(STATUS "SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
# 添加SDL2的库文件搜索路径（x64版本）
set(SDL2_LIB_DIR "${SDL2_BASE_DIR}/lib/x64")
message(STATUS "SDL2_LIB_DIR: ${SDL2_LIB_DIR}")

# 将这些路径添加到CMake的全局搜索路径
include_directories(${SDL2_INCLUDE_DIR})
if(NOT EXISTS ${SDL2_INCLUDE_DIR})
message(FATAL_ERROR "SDL2头文件目录不存在: ${SDL2_INCLUDE_DIR}")
endif()

link_directories(${SDL2_LIB_DIR} ${CMAKE_SOURCE_DIR}/lib)
if(NOT EXISTS ${SDL2_LIB_DIR})
message(FATAL_ERROR "SDL2库文件目录不存在: ${SDL2_LIB_DIR}")
endif()

# 输出目录控制
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置 CMAKE_PREFIX_PATH

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)
set(CMAKE_PREFIX_PATH
    ${THIRDPARTY_DIR}/json;
    ${THIRDPARTY_DIR}/SDL2
)
set_property(DIRECTORY PROPERTY CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})

add_subdirectory(${THIRDPARTY_DIR}/glm)
add_subdirectory(${THIRDPARTY_DIR}/OpenXLSX)
add_subdirectory(${THIRDPARTY_DIR}/box2d-lite)

add_subdirectory(src)
