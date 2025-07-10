set(LOGGER_SOURCES
    Logger.cpp
    )

add_library(Logger STATIC ${LOGGER_SOURCES})
target_include_directories(Logger PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    Logger PUBLIC
    spdlog::spdlog
    )

set_target_properties(
    Logger PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
    DEBUG_POSTFIX "d"
)

# 在 CMakeLists.txt 中设置日志文件路径
set(LOG_FILE_PATH "${CMAKE_SOURCE_DIR}/logs/app.log")
message(STATUS "Log file path: ${LOG_FILE_PATH}")
# 将日志文件路径定义为编译时宏
add_definitions(-DLOG_FILE_PATH="${LOG_FILE_PATH}")

add_library(game::logger ALIAS Logger)