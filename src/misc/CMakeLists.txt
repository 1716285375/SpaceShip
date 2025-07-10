
set(MISC_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
    )


add_library(Utils STATIC ${MISC_SOURCES}
)

target_include_directories(Utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(Utils PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
    DEBUG_POSTFIX "d" # Debug 版本的可执行文件后缀
)

target_link_libraries(
    Utils PRIVATE
    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)

add_library(game::utils ALIAS Utils)