set(COMPONENT_SOURCES
    Component.cpp
    CTransform.cpp)

add_library(Components STATIC ${COMPONENT_SOURCES})

target_include_directories(
    Components PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${GLM_INCLUDE_DIRS}
)

target_link_libraries(
    Components PRIVATE
    spdlog::spdlog
)

add_library(game::components ALIAS Components)