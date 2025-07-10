
set(RESOURCE_SOURCES
    Resource.cpp
    TextureResource.cpp
    FontResource.cpp
    SoundResource.cpp
    MusicResource.cpp
    AnimationResource.cpp
    ResourceManager.cpp
    )

# 创建场景库
add_library(Resources STATIC ${RESOURCE_SOURCES})
target_include_directories(Resources PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(Resources PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
    DEBUG_POSTFIX "d" # Debug 版本的可执行文件后缀
)

target_link_libraries(
    Resources PRIVATE
    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    nlohmann_json::nlohmann_json
    spdlog::spdlog
)

add_library(game::resources ALIAS Resources)