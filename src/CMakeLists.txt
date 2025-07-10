set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SceneMain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SceneTitle.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SceneEnd.cpp"
)

# 添加可执行文件
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

if (WIN32)
    list(APPEND SOURCES ${ROOT_DIR}/resources.rc)
endif()
message(STATUS "SOURCES: ${SOURCES}")

# 跨平台配置
if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(UNIX AND NOT APPLE)
    add_compile_options(-pthread)
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
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

# 链接指定库
target_link_libraries(
    ${TARGET}
    PRIVATE
    debug game::scenes # Debug 版本
    optimized game::scenes # Release 版本
    debug game::resources # Debug 版本
    optimized game::resources # Release 版本
    # debug game::input # Debug 版本
    # optimized game::input # Release 版本
    # debug game::entity # Debug 版本
    # optimized game::entity # Release 版本
    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    glm::glm
    nlohmann_json::nlohmann_json
    OpenXLSX::OpenXLSX
)

# 设置可执行文件输出目录
set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
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

# 添加子目录（使用命名空间）
add_subdirectory(scenes)
add_subdirectory(resources)
# add_subdirectory(input)
add_subdirectory(entity)