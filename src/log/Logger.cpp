#include "Logger.h"
#include <iostream>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>



void initAsyncLogger() {
    try {
        // 初始化线程池
        spdlog::init_thread_pool(8192, 1);

        // 创建异步日志记录器
        auto async_logger = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>("async_logger", "..\..\logs\async_game.log", true);
        if (!async_logger) {
            throw spdlog::spdlog_ex("Failed to create async logger");
        }

        // 设置日志格式
        async_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [thread %t] %v");

        // 设置日志级别
        async_logger->set_level(spdlog::level::info);

        // 设置为默认日志记录器
        spdlog::set_default_logger(async_logger);

        // 输出日志信息
        spdlog::info("Asynchronous logger initialized successfully");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Asynchronous logger initialization failed: " << ex.what() << std::endl;
    }
}