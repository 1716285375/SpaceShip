

# 过渡效果子系统
set (SCENES_TRANSITION_SOURCES
    transitions/SceneTransition.cpp)

# 配置加载子系统
set(SCENES_CONFIG_SOURCES
    config/SceneConfig.cpp
    config/SceneLoader.cpp)

# 场景管理
set(SCENES_SOURCES
    SceneManager.cpp
    Scene.cpp
    ${SCENES_TRANSITION_SOURCES}
    ${SCENES_CONFIG_SOURCES}
    )

# 场景实现
list(APPEND SCENES_SOURCES
    MenuScene.cpp
    LevelScene.cpp
)

# 创建场景库
add_library(Scenes STATIC ${SCENES_SOURCES})

target_include_directories(Scenes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/transitions
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    )

target_link_libraries(Scenes PRIVATE
    nlohmann_json::nlohmann_json
)

# 显式设置链接器语言、指定 Scene.dll 生成的目录

set_target_properties(Scenes PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
    DEBUG_POSTFIX "d" # Debug 版本的可执行文件后缀
)

# 创建别名目标方便外层引用
add_library(game::scenes ALIAS Scenes)