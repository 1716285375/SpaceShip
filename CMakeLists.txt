# 标题
cmake_minimum_required(VERSION 3.10.0)
project(SpaceShoot VERSION 0.1.0 LANGUAGES C CXX)


# 设置SDL2库的根目录（根据你的实际路径修改）

set(SDL2_BASE_DIR    "${CMAKE_SOURCE_DIR}/SDL2")
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

link_directories(${SDL2_LIB_DIR})
if(NOT EXISTS ${SDL2_LIB_DIR})
message(FATAL_ERROR "SDL2库文件目录不存在: ${SDL2_LIB_DIR}")
endif()




# 添加可执行文件
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})
set(SOURCES
                "src/main.cpp"
                "src/Game.cpp"
                "src/Scene.cpp"
                "src/SceneMain.cpp"
                "src/SceneTitle.cpp"
                "src/SceneEnd.cpp"
            )

if (WIN32)
    list(APPEND SOURCES resources.rc)
endif()
add_executable(${TARGET} ${SOURCES})


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
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# 链接指定库
target_link_libraries(
    ${TARGET}
    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    )


# 复制SDL2的DLL文件到可执行文件目录（Windows必需）
if(WIN32)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIB_DIR}/SDL2.dll"
        "${SDL2_LIB_DIR}/SDL2_image.dll"
        "${SDL2_LIB_DIR}/SDL2_mixer.dll"
        "${SDL2_LIB_DIR}/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${TARGET}>
    )
endif()

# 不显示控制台窗口
if (MSVC)
    target_link_options(${TARGET} PRIVATE /SUBSYSTEM:WINDOWS)
endif()