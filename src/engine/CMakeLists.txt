
set(ENGINE_SOURCES
    Engine.cpp)

add_library(Engine STATIC ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/log
    ${CMAKE_SOURCE_DIR}/src/scenes
    ${CMAKE_SOURCE_DIR}/src/resources
)

target_link_libraries(Engine PUBLIC
    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    spdlog::spdlog
    )

set_target_properties(
    Engine PROPERTIES
    LINKER_LANGUAGE CXX
    CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug
    CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
    DEBUG_POSTFIX "d"
)

add_library(game::engine ALIAS Engine)