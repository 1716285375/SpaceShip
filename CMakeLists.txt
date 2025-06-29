# 标题
cmake_minimum_required(VERSION 3.10.0)
project(SpaceShoot VERSION 0.1.0 LANGUAGES C CXX)

# 添加可执行文件
set(TARGET ${PROJECT_NAMME}-${CMAKE_SYSTEM_NAME})
add_executable(${TARGET} main.cpp)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# 查找Cmake预设
find_package(SDL2 REQUIRED)

# 链接指定库
target_link_libraries(${TARGET}
                    SDL2::SDL2main
                    SDL2::SDL2)