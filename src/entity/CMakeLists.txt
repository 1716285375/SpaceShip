set(ENTITY_SOURCES
    Entity.cpp
    EntityManager.cpp)


add_library(Entity STATIC ${ENTITY_SOURCES})

target_include_directories(Entity PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/engine/core/component
    ${GLM_INCLUDE_DIRS}
    )