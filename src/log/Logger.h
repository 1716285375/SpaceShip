#ifndef LOGGER_H
#define LOGGER_H


#include "spdlog/spdlog.h"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>



void initAsyncLogger();
#endif // !LOGGER_H
